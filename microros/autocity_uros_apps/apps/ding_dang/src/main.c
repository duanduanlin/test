#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <rmw_microros/rmw_microros.h>
#include <microros_transports.h>

#include <std_msgs/msg/header.h>

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include <zephyr.h>

#define STRING_BUFFER_LEN 50

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printf("Failed status on line %d: %d. Aborting.\n",__LINE__,(int)temp_rc); return 1;}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printf("Failed status on line %d: %d. Continuing.\n",__LINE__,(int)temp_rc);}}

rcl_publisher_t ding_publisher;
rcl_subscription_t dang_subscriber;

std_msgs__msg__Header outcoming_ding;
std_msgs__msg__Header incoming_dang;

int device_id;
int seq_no;
int dang_count;

void ding_timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
	(void) last_call_time;

	if (timer != NULL) {

		seq_no = rand();
		sprintf(outcoming_ding.frame_id.data, "%d_%d", seq_no, device_id);
		outcoming_ding.frame_id.size = strlen(outcoming_ding.frame_id.data);

		// Fill the message timestamp
		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		outcoming_ding.stamp.sec = ts.tv_sec;
		outcoming_ding.stamp.nanosec = ts.tv_nsec;

		// Reset the dang count and publish the ding message
		dang_count = 0;
		rcl_publish(&ding_publisher, (const void*)&outcoming_ding, NULL);
		printf("ding send seq %s\n", outcoming_ding.frame_id.data);
	}
}


void dang_subscription_callback(const void * msgin)
{
	const std_msgs__msg__Header * msg = (const std_msgs__msg__Header *)msgin;

	if(strcmp(outcoming_ding.frame_id.data, msg->frame_id.data) == 0) {
			dang_count++;
			printf("dang for seq %s (%d)\n", msg->frame_id.data, dang_count);
	}
}


void main(void)
{
	// Set custom transports
	rmw_uros_set_custom_transport(
		MICRO_ROS_FRAMING_REQUIRED,
		(void *) &default_params,
		zephyr_transport_open,
		zephyr_transport_close,
		zephyr_transport_write,
		zephyr_transport_read
	);

	// Init micro-ROS
	rcl_allocator_t allocator = rcl_get_default_allocator();
	rclc_support_t support;

	// create init_options
	RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

	// create node
	rcl_node_t node;
	RCCHECK(rclc_node_init_default(&node, "dingdang_node", "", &support));

	// Create a reliable ding publisher
	RCCHECK(rclc_publisher_init_default(&ding_publisher, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Header), "/microROS/ding"));

	// Create a best effort  dang subscriber
	RCCHECK(rclc_subscription_init_best_effort(&dang_subscriber, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Header), "/microROS/dang"));


	// Create a 3 seconds ding timer timer,
	rcl_timer_t timer;
	RCCHECK(rclc_timer_init_default(&timer, &support, RCL_MS_TO_NS(2000), ding_timer_callback));


	// Create executor
	rclc_executor_t executor;
	RCCHECK(rclc_executor_init(&executor, &support.context, 3, &allocator));
	RCCHECK(rclc_executor_add_timer(&executor, &timer));
	RCCHECK(rclc_executor_add_subscription(&executor, &dang_subscriber, &incoming_dang, &dang_subscription_callback, ON_NEW_DATA));

	// Create and allocate the dingdang messages

	char outcoming_ding_buffer[STRING_BUFFER_LEN];
	outcoming_ding.frame_id.data = outcoming_ding_buffer;
	outcoming_ding.frame_id.capacity = STRING_BUFFER_LEN;

	char incoming_dang_buffer[STRING_BUFFER_LEN];
	incoming_dang.frame_id.data = incoming_dang_buffer;
	incoming_dang.frame_id.capacity = STRING_BUFFER_LEN;

	device_id = rand();

	while(1){
		rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
		usleep(100000);
	}

	RCCHECK(rcl_publisher_fini(&ding_publisher, &node));
	RCCHECK(rcl_subscription_fini(&dang_subscriber, &node));
	RCCHECK(rcl_node_fini(&node));
}
