import os
from glob import glob
from setuptools import find_packages, setup

package_name = 'system_analysis'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('lib', package_name), glob(f'{package_name}/*.py')),
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
            'system_analysis = system_analysis:main'
        ],
    },
)
