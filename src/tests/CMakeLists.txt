


  add_library(gmock ${GOOGLETEST_DIR}/src/gtest-all.cc ${GOOGLEMOCK_DIR}/src/gmock-all.cc)

  target_include_directories(gmock PUBLIC ${GOOGLETEST_DIR} ${GOOGLEMOCK_DIR}
          ${GOOGLETEST_DIR}/include ${GOOGLEMOCK_DIR}/include)



  add_executable(${PROJECT_NAME}Test ${PROJECT_NAME}Test.cpp )
  #add_dependencies(${PROJECT_NAME}Test gmock)



  target_link_libraries(${PROJECT_NAME}Test  PUBLIC gmock  ${PROJECT_NAME})

  # install(TARGETS ${PROJECT_NAME}Test
  #   # IMPORTANT: Add the bar executable to the "export-set"
  #   EXPORT ${PROJECT_NAME}Targets
  #   RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
