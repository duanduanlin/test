// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file HelloWorldPublisher.cpp
 *
 */

#include "HelloWorldPubSubTypes.hpp"

#include <chrono>
#include <thread>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantListener.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

using namespace eprosima::fastdds::dds;

class HelloWorldPublisher
{
private:
    HelloWorld hello_;

    DomainParticipant *participant_;

    Publisher *publisher_;

    Topic *topic_;

    DataWriter *writer_;

    TypeSupport type_;

    class CustomDomainParticipantListener : public DomainParticipantListener
    {

    public:
        CustomDomainParticipantListener()
            : DomainParticipantListener()
        {
        }

        virtual ~CustomDomainParticipantListener()
        {
        }

        void on_participant_discovery(
            DomainParticipant *participant,
            eprosima::fastdds::rtps::ParticipantDiscoveryStatus status,
            const ParticipantBuiltinTopicData &info,
            bool &should_be_ignored) override
        {
            should_be_ignored = false;
            if (status == eprosima::fastdds::rtps::ParticipantDiscoveryStatus::DISCOVERED_PARTICIPANT)
            {
                std::cout << "New participant discovered" << std::endl;
                // The following line can be modified to evaluate whether the discovered participant should be ignored
                // (usually based on fields present in the discovery information)
                bool ignoring_condition = false;
                if (ignoring_condition)
                {
                    should_be_ignored = true; // Request the ignoring of the discovered participant
                }
            }
            else if (status == eprosima::fastdds::rtps::ParticipantDiscoveryStatus::REMOVED_PARTICIPANT ||
                     status == eprosima::fastdds::rtps::ParticipantDiscoveryStatus::DROPPED_PARTICIPANT)
            {
                std::cout << "Participant lost" << std::endl;
            }
        }

#if HAVE_SECURITY
        void onParticipantAuthentication(
            DomainParticipant *participant,
            eprosima::fastdds::rtps::ParticipantAuthenticationInfo &&info) override
        {
            if (info.status == eprosima::fastdds::rtps::ParticipantAuthenticationInfo::AUTHORIZED_PARTICIPANT)
            {
                std::cout << "A participant was authorized" << std::endl;
            }
            else if (info.status == eprosima::fastdds::rtps::ParticipantAuthenticationInfo::UNAUTHORIZED_PARTICIPANT)
            {
                std::cout << "A participant failed authorization" << std::endl;
            }
        }

#endif // if HAVE_SECURITY

        void on_data_reader_discovery(
            DomainParticipant *participant,
            eprosima::fastdds::rtps::ReaderDiscoveryStatus reason,
            const eprosima::fastdds::rtps::SubscriptionBuiltinTopicData &info,
            bool &should_be_ignored) override
        {
            should_be_ignored = false;
            if (reason == eprosima::fastdds::rtps::ReaderDiscoveryStatus::DISCOVERED_READER)
            {
                std::cout << "New datareader discovered" << std::endl;
                // The following line can be modified to evaluate whether the discovered datareader should be ignored
                // (usually based on fields present in the discovery information)
                bool ignoring_condition = false;
                if (ignoring_condition)
                {
                    should_be_ignored = true; // Request the ignoring of the discovered datareader
                }
            }
            else if (reason == eprosima::fastdds::rtps::ReaderDiscoveryStatus::REMOVED_READER)
            {
                std::cout << "Datareader lost" << std::endl;
            }
        }

        void on_data_writer_discovery(
            DomainParticipant *participant,
            eprosima::fastdds::rtps::WriterDiscoveryStatus reason,
            const eprosima::fastdds::dds::PublicationBuiltinTopicData &info,
            bool &should_be_ignored) override
        {
            static_cast<void>(participant);
            static_cast<void>(info);

            should_be_ignored = false;
            if (reason == eprosima::fastdds::rtps::WriterDiscoveryStatus::DISCOVERED_WRITER)
            {
                std::cout << "New datawriter discovered" << std::endl;
                // The following line can be modified to evaluate whether the discovered datawriter should be ignored
                // (usually based on fields present in the discovery information)
                bool ignoring_condition = false;
                if (ignoring_condition)
                {
                    should_be_ignored = true; // Request the ignoring of the discovered datawriter
                }
            }
            else if (reason == eprosima::fastdds::rtps::WriterDiscoveryStatus::REMOVED_WRITER)
            {
                std::cout << "Datawriter lost" << std::endl;
            }
        }
    } participantListener_;

    class PubListener : public DataWriterListener
    {
    public:
        PubListener()
            : matched_(0)
        {
        }

        ~PubListener() override
        {
        }

        void on_publication_matched(
            DataWriter *,
            const PublicationMatchedStatus &info) override
        {
            if (info.current_count_change == 1)
            {
                matched_ = info.total_count;
                std::cout << "Publisher matched." << std::endl;
            }
            else if (info.current_count_change == -1)
            {
                matched_ = info.total_count;
                std::cout << "Publisher unmatched." << std::endl;
            }
            else
            {
                std::cout << info.current_count_change
                          << " is not a valid value for PublicationMatchedStatus current count change." << std::endl;
            }
        }

        void on_offered_deadline_missed(
            DataWriter *writer,
            const OfferedDeadlineMissedStatus &status) override
        {
            static_cast<void>(writer);
            static_cast<void>(status);
            std::cout << "Some data could not be delivered on time" << std::endl;
        }

        void on_offered_incompatible_qos(
            DataWriter *writer,
            const OfferedIncompatibleQosStatus &status) override
        {
            std::cout << "Found a remote Topic with incompatible QoS (QoS ID: " << status.last_policy_id << ")" << std::endl;
        }

        void on_liveliness_lost(
            DataWriter *writer,
            const LivelinessLostStatus &status) override
        {
            static_cast<void>(writer);
            static_cast<void>(status);
            std::cout << "Liveliness lost. Matched Subscribers will consider us offline" << std::endl;
        }

        void on_unacknowledged_sample_removed(
            DataWriter *writer,
            const InstanceHandle_t &instance) override
        {
            static_cast<void>(writer);
            static_cast<void>(instance);
            std::cout << "Sample removed unacknowledged" << std::endl;
        }

        std::atomic_int matched_;

    } listener_;

public:
    HelloWorldPublisher()
        : participant_(nullptr), publisher_(nullptr), topic_(nullptr), writer_(nullptr), type_(new HelloWorldPubSubType())
    {
    }

    virtual ~HelloWorldPublisher()
    {
        if (writer_ != nullptr)
        {
            publisher_->delete_datawriter(writer_);
        }
        if (publisher_ != nullptr)
        {
            participant_->delete_publisher(publisher_);
        }
        if (topic_ != nullptr)
        {
            participant_->delete_topic(topic_);
        }
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
    }

    //! Initialize the publisher
    bool init()
    {
        hello_.index(0);
        hello_.message("HelloWorld");

        DomainParticipantQos participantQos;
        participantQos.name("Participant_publisher");
        // participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);
        participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos, &participantListener_);

        if (participant_ == nullptr)
        {
            return false;
        }

        // Register the Type
        type_.register_type(participant_);

        // Create the publications Topic
        topic_ = participant_->create_topic("HelloWorldTopic", "HelloWorld", TOPIC_QOS_DEFAULT);

        if (topic_ == nullptr)
        {
            return false;
        }

        // Create the Publisher
        publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);

        if (publisher_ == nullptr)
        {
            return false;
        }

        // Create the DataWriter
        writer_ = publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, &listener_);

        if (writer_ == nullptr)
        {
            return false;
        }
        return true;
    }

    //! Send a publication
    bool publish()
    {
        if (listener_.matched_ > 0)
        {
            hello_.index(hello_.index() + 1);
            writer_->write(&hello_);
            return true;
        }
        return false;
    }

    //! Run the Publisher
    void run(
        uint32_t samples)
    {
        uint32_t samples_sent = 0;
        while (samples_sent < samples)
        {
            if (publish())
            {
                samples_sent++;
                std::cout << "Message: " << hello_.message() << " with index: " << hello_.index()
                          << " SENT" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
};

int main(
    int argc,
    char **argv)
{
    std::cout << "Starting publisher." << std::endl;
    uint32_t samples = 10;

    HelloWorldPublisher *mypub = new HelloWorldPublisher();
    if (mypub->init())
    {
        mypub->run(samples);
    }

    delete mypub;
    return 0;
}
