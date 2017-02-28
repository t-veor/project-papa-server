include_directories(${include_directories} include)

file(glob sources "src/*.cpp")

add_library(osc_interface ${sources})

target_include_directories(scope_interface public
    $<build_interface:${cmake_current_source_dir}/include>
    $<install_interface:include>
    private src)
