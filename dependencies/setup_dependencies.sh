# This script's purpose is downloading dependencies,
# performing required configuration/compilation/purging
# and organising them into desired form.

rm -rf gl3w gl3w_repo \
       glfw glfw_repo \
       imgui imgui_repo

##### GLFW #####
git clone https://github.com/glfw/glfw.git glfw_repo
cd glfw_repo
    git checkout 3.2.1
    rm -rf .git .gitignore .github docs examples tests .appveyor.yml .travis.yml
cd ..
mv glfw_repo glfw

##### GL3W #####
git clone https://github.com/skaslev/gl3w.git gl3w_repo
cd gl3w_repo
    git checkout master
    cmake . && make
cd ..
mkdir -p gl3w/GL
cp gl3w_repo/include/GL/gl3w.h \
   gl3w_repo/include/GL/glcorearb.h \
   gl3w_repo/src/gl3w.c \
   gl3w/GL/
rm -rf gl3w_repo

##### ImGUI #####
git clone https://github.com/ocornut/imgui.git imgui_repo
mkdir imgui_impl_glfw_gl3
cd imgui_repo
    git checkout v1.52
    cp examples/opengl3_example/imgui_impl_glfw_gl3.h \
       examples/opengl3_example/imgui_impl_glfw_gl3.cpp \
       ../imgui_impl_glfw_gl3
    rm -rf .git .gitignore examples .travis.yml TODO.txt
cd ..
mv imgui_repo imgui