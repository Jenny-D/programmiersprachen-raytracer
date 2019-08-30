add_executable(example example.cpp)

target_link_libraries(example ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS example DESTINATION .)

add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

add_executable(sdfGenerator sdfGenerator.cpp)

target_link_libraries(sdfGenerator ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(sdfGenerator glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS sdfGenerator DESTINATION .)

# Build tests
add_executable(tests
  tests.cpp)
target_link_libraries(tests
  ${FRAMEWORK_NAME}
  ${GLFW_LIBRARIES}
  )

