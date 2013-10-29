set(MODULE TaskBase)

set(SRCS
AliRsnTask.cxx
AliRsnTaskEmpty.cxx
AliRsnTaskCanvas.cxx
)

set(INCLUDE_DIRS_DEP )

add_module(${MODULE} "${SRCS}" "${INCLUDE_DIRS_DEP}")
