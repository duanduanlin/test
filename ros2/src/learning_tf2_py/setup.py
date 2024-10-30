'''
Author: hanson
Date: 2024-10-30 14:27:46
LastEditors: hanson
LastEditTime: 2024-10-30 16:25:25
Description:
FilePath: \test\test\ros2\src\learning_tf2_py\setup.py
'''
import os
from glob import glob
from setuptools import find_packages, setup

package_name = 'learning_tf2_py'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.[pxy][yma]*'))),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='hanson',
    maintainer_email='hanson@citygo.com.cn',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'static_turtle_tf2_broadcaster = learning_tf2_py.static_turtle_tf2_broadcaster:main',
            'turtle_tf2_broadcaster = learning_tf2_py.turtle_tf2_broadcaster:main',
            'turtle_tf2_listener = learning_tf2_py.turtle_tf2_listener:main',
            'fixed_frame_tf2_broadcaster = learning_tf2_py.fixed_frame_tf2_broadcaster:main',
            'dynamic_frame_tf2_broadcaster = learning_tf2_py.dynamic_frame_tf2_broadcaster:main',
        ],
    },
)
