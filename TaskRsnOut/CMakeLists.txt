set(MODULE TaskRsnOut)

set(SRCS
AliRsnTaskNSigma.cxx
)

set(INCLUDE_DIRS_DEP ${CMAKE_SOURCE_DIR}/TaskBase)

add_module(${MODULE} "${SRCS}" "${INCLUDE_DIRS_DEP}")
