#!/bin/bash
# By Pytel

python_dependencies="pip-dependencies.txt"
apt_dependencies="apt-dependencies.txt"

# Install apt dependencies
sudo apt-get update
if [ -f $apt_dependencies ]; then
    xargs sudo apt-get -y install < $apt_dependencies
fi

# Install python dependencies
if [ -f $python_dependencies ]; then 
    pip install -r $python_dependencies
fi

echo -e "Done!"