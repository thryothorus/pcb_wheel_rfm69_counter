include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")
set(radio_wheel_counter_default_library_list )
# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm) 
if(radio_wheel_counter_default_FILE_GROUP_assemble)
    add_library(radio_wheel_counter_default_assemble OBJECT ${radio_wheel_counter_default_FILE_GROUP_assemble})
    radio_wheel_counter_default_assemble_rule(radio_wheel_counter_default_assemble)
    list(APPEND radio_wheel_counter_default_library_list "$<TARGET_OBJECTS:radio_wheel_counter_default_assemble>")
endif()

# Handle files with suffix S 
if(radio_wheel_counter_default_FILE_GROUP_assemblePreprocess)
    add_library(radio_wheel_counter_default_assemblePreprocess OBJECT ${radio_wheel_counter_default_FILE_GROUP_assemblePreprocess})
    radio_wheel_counter_default_assemblePreprocess_rule(radio_wheel_counter_default_assemblePreprocess)
    list(APPEND radio_wheel_counter_default_library_list "$<TARGET_OBJECTS:radio_wheel_counter_default_assemblePreprocess>")
endif()

# Handle files with suffix [cC] 
if(radio_wheel_counter_default_FILE_GROUP_compile)
    add_library(radio_wheel_counter_default_compile OBJECT ${radio_wheel_counter_default_FILE_GROUP_compile})
    radio_wheel_counter_default_compile_rule(radio_wheel_counter_default_compile)
    list(APPEND radio_wheel_counter_default_library_list "$<TARGET_OBJECTS:radio_wheel_counter_default_compile>")
endif()

if (BUILD_LIBRARY)
        message(STATUS "Building LIBRARY")
        add_library(${radio_wheel_counter_default_image_name} ${radio_wheel_counter_default_library_list})
        foreach(lib ${radio_wheel_counter_default_FILE_GROUP_link})
        target_link_libraries(${radio_wheel_counter_default_image_name} PRIVATE ${CMAKE_CURRENT_LIST_DIR} /${lib})
        endforeach()
        add_custom_command(
            TARGET ${radio_wheel_counter_default_image_name}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${radio_wheel_counter_default_output_dir}
    COMMAND ${CMAKE_COMMAND} -E copy lib${radio_wheel_counter_default_image_name}.a ${radio_wheel_counter_default_output_dir}/${radio_wheel_counter_default_original_image_name})
else()
    message(STATUS "Building STANDARD")
    add_executable(${radio_wheel_counter_default_image_name} ${radio_wheel_counter_default_library_list})
    foreach(lib ${radio_wheel_counter_default_FILE_GROUP_link})
    target_link_libraries(${radio_wheel_counter_default_image_name} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/${lib})
endforeach()
    radio_wheel_counter_default_link_rule(${radio_wheel_counter_default_image_name})
    
add_custom_command(
    TARGET ${radio_wheel_counter_default_image_name}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${radio_wheel_counter_default_output_dir}
    COMMAND ${CMAKE_COMMAND} -E copy ${radio_wheel_counter_default_image_name} ${radio_wheel_counter_default_output_dir}/${radio_wheel_counter_default_original_image_name})
endif()
