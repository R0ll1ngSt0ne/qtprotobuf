set(TARGET qtprotobuf_qml_test)

find_package(Qt5 COMPONENTS Core Quick Network Test QuickTest REQUIRED)
find_package(QtProtobufProject COMPONENTS QtProtobuf REQUIRED)

include(${QTPROTOBUF_CMAKE_DIR}/QtProtobufCommon.cmake)

file(GLOB SOURCES main.cpp)
file(GLOB QML_FILES qml/tst_simple.qml)

add_executable(${TARGET} ${SOURCES} ${QML_FILES})
target_link_libraries(${TARGET} Qt5::Core Qt5::Qml Qt5::Network Qt5::Quick Qt5::Test Qt5::QuickTest qtprotobuf_test_qtprotobuf_gen QtProtobufProject::QtProtobuf)

add_target_qml(TARGET ${TARGET} QML_FILES ${QML_FILES})
add_target_windeployqt(TARGET ${TARGET} QML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qml)

add_test(NAME ${TARGET} COMMAND ${TARGET})

set(QTPROTOBUF_QML2_IMPORT_PATH $<TARGET_FILE_DIR:protobufquickplugin>/..)

set_tests_properties(${TARGET} PROPERTIES
    ENVIRONMENT QML2_IMPORT_PATH=${QTPROTOBUF_QML2_IMPORT_PATH})
