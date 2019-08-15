#   Copyright 2019 Comcast Cable Communications Management, LLC
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

set(PROJ_ULTRIE ultrie)

file(GLOB HEADERS ultrie.h)
set(SOURCES ultrie.c find.c print.c)

add_library(${PROJ_ULTRIE} STATIC ${HEADERS} ${SOURCES})
add_library(${PROJ_ULTRIE}.shared SHARED ${HEADERS} ${SOURCES})
set_target_properties(${PROJ_ULTRIE}.shared PROPERTIES OUTPUT_NAME ${PROJ_ULTRIE})
set_property(TARGET ${PROJ_ULTRIE} PROPERTY C_STANDARD 99)
set_property(TARGET ${PROJ_ULTRIE}.shared PROPERTY C_STANDARD 99)

install (TARGETS ${PROJ_ULTRIE} DESTINATION lib${LIB_SUFFIX})
install (TARGETS ${PROJ_ULTRIE}.shared DESTINATION lib${LIB_SUFFIX})
install (FILES ultrie.h DESTINATION include/${PROJ_ULTRIE})
