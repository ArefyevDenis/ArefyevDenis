cmake_minimum_required (VERSION 3.8)

message("---------------------Kernel_module-------------------------")

execute_process(COMMAND uname -r OUTPUT_VARIABLE FOO)

#message("UNAME: /usr/src/linux-headers-${FOO}/include/")
message("CMAKE_MAKE_PROGRAM: ${CMAKE_MAKE_PROGRAM}" )
#include_directories("/usr/src/linux-headers-${FOO}/include/")
include_directories("/usr/src/linux-headers-4.15.0-20-generic/include")
message("PROJECT_SOURCE_DIR: ${CMAKE_BINARY_DIR}/bin" ) # PROJECT_SOURCE_DIR
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin  )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin  )

#--------------------------------------------------------------------------------------------#
# Внимание qctreator при теневой сборке создаёт очень длинные имена каталогов это плохо
# cmake не может создать внутренний каталог, поо этому, необходимо в ручную задать катол сборки
#--------------------------------------------------------------------------------------------#

SET( MODULE_NAME            lkm_drv)

SET( MODULE_SOURCE_FILES    lkm_driver.c)

SET( MODULE_FILE            ${MODULE_NAME}.ko)

SET( MODULE_OUTPUT_DIR      ${CMAKE_BINARY_DIR}/bin/${MODULE_NAME})

SET( KERNEL_DIR             "/lib/modules/${CMAKE_SYSTEM_VERSION}/build")

SET( KBUILD_COMMAND         ${CMAKE_MAKE_PROGRAM} -C ${KERNEL_DIR} M=${MODULE_OUTPUT_DIR} modules )

CONFIGURE_FILE( Kbuild.in   ${MODULE_OUTPUT_DIR}/Kbuild )

FOREACH( MODULE_SOURCE_FILE ${MODULE_SOURCE_FILES} )
    CONFIGURE_FILE(
    ${MODULE_SOURCE_FILE}
    ${MODULE_OUTPUT_DIR}/${MODULE_SOURCE_FILE}
    COPYONLY
    )
ENDFOREACH( MODULE_SOURCE_FILE )

#------------------------------------------------------------------------------------------------#
ADD_CUSTOM_COMMAND(
    OUTPUT ${MODULE_OUTPUT_DIR}/${MODULE_FILE}
    COMMAND ${KBUILD_COMMAND}
    WORKING_DIRECTORY ${MODULE_OUTPUT_DIR}
    DEPENDS ${MODULE_SOURCE_FILES} Kbuild.in
    VERBATIM
    )
ADD_CUSTOM_TARGET(${MODULE_NAME}
    ALL
    DEPENDS ${MODULE_OUTPUT_DIR}/${MODULE_FILE} )
#------------------------------------------------------------------------------------------------#


#Set( MODULE_OUTPUT_FILES    w00t.o
#                            w00t.mod.c
#                            w00t.mod.o
#                            w00t.ko
#                            .w00t.o.cmd
#                            .w00t.ko.cmd
#                            .w00t.mod.o.cmd
#                            .tmp_versions/w00t.mod
#                            .tmp_versions/ )

#Set( MODULE_SOURCE_FILES    Kbuild
#                            w00t.c )
#Set( DRIVER_FILE        w00t.ko )
#Set( DRIVER_TARGET_NAME w00t-module )
#Set( DRIVER_BIN_FILE    ${CMAKE_BINARY_DIR}/bin/${DRIVER_FILE} )
#Set( MODULE_SOURCE_DIR  ${PROJECT_SOURCE_DIR}/src/w00t )

#Set( KERNEL_DIR "/lib/modules/${CMAKE_SYSTEM_VERSION}/build" )

#Set( KBUILD_CMD ${CMAKE_MAKE_PROGRAM} -C ${KERNEL_DIR}  M=${MODULE_SOURCE_DIR}  modules )

##------------------------------------------------------------------------------------------------#
#Add_Custom_Command( OUTPUT  ${DRIVER_BIN_FILE} ${MODULE_OUTPUT_FILES}
#    COMMAND ${KBUILD_CMD}
#    COMMAND cp -f ${DRIVER_FILE} ${DRIVER_BIN_FILE}
#    WORKING_DIRECTORY ${MODULE_SOURCE_DIR}
#    DEPENDS ${MODULE_SOURCE_FILES} VERBATIM )

#Add_Custom_Target ( ${DRIVER_TARGET_NAME}
#    ALL
#    DEPENDS ${DRIVER_BIN_FILE} )
##------------------------------------------------------------------------------------------------#

message("---------------------Kernel_module-------------------------")
