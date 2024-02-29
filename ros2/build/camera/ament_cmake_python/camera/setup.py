from setuptools import find_packages
from setuptools import setup

setup(
    name='camera',
    version='0.0.0',
    packages=find_packages(
        include=('camera', 'camera.*')),
)
