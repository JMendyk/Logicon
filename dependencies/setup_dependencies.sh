#!/usr/bin/env bash

# This script's purpose is downloading dependencies,
# performing required configuration/compilation/purging
# and organising them into desired form.

HISTFILE=`pwd`/dependencies_history.txt

# Change datetime's locale to get month/weekday names in english
LC_TIME_copy=$LC_TIME
LC_TIME=en_US.UTF-8
HEADER="Updating dependencies - $(date "+%a %b %d %T %Y %z")"
LC_TIME=$LC_TIME_copy


function log_dependency {
    info=`git log --pretty=format:"%h, %ad : %s" | head -n 1`
    echo "Dependency: $1" >> $HISTFILE
    echo $info >> $HISTFILE
}

function log_dependency_file {
    info=`git log --pretty=format:"%h, %ad : %s" --follow $2 | head -n 1`
    echo "Dependency: $1" >> $HISTFILE
    echo $info >> $HISTFILE
}

rm -rf gl3w gl3w_repo \
       glfw glfw_repo \
       imgui imgui_repo \
       imgui_impl_glfw_gl3 \
       json json_repo \
       stb_repo \
       stb_image

echo $HEADER >> $HISTFILE

##### GLFW #####
git clone https://github.com/glfw/glfw.git glfw_repo
cd glfw_repo
    git checkout 3.2.1
    log_dependency glfw
    rm -rf .git .gitignore .github docs examples tests .appveyor.yml .travis.yml
cd ..
mv glfw_repo glfw

##### GL3W #####
git clone https://github.com/skaslev/gl3w.git gl3w
cd gl3w
    git checkout master
    log_dependency gl3w
    cmake . && make
    rm -rf .git .gitignore
cd ..

##### ImGUI #####
git clone https://github.com/ocornut/imgui.git imgui_repo
mkdir imgui_impl_glfw_gl3
cd imgui_repo
    git checkout v1.52
    log_dependency imgui
    cp examples/opengl3_example/imgui_impl_glfw_gl3.h \
       examples/opengl3_example/imgui_impl_glfw_gl3.cpp \
       ../imgui_impl_glfw_gl3
    rm -rf .git .gitignore examples .travis.yml TODO.txt
cd ..
mv imgui_repo imgui

##### json #####
mkdir -p json/json
git clone https://github.com/nlohmann/json.git json_repo
cd json_repo
    git checkout v2.1.1
    log_dependency json
    cp src/json.hpp ../json/json
cd ..
rm -rf json_repo

##### stb_image #####
mkdir -p stb_image/stb_image
git clone https://github.com/nothings/stb stb_repo
cd stb_repo
    git checkout master
    log_dependency_file stb_image stb_image.h
    cp stb_image.h ../stb_image/stb_image/
cd ..
rm -rf stb_repo

echo $HEADER | sed 's/./-/g' >> $HISTFILE
echo "" >> $HISTFILE
