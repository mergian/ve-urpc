SET(VH_SRC
	${CMAKE_CURRENT_LIST_DIR}/pingpong.c
	${CMAKE_CURRENT_LIST_DIR}/ping_vh.c
)

SET(VE_SRC
	${CMAKE_CURRENT_LIST_DIR}/pingpong.c
	${CMAKE_CURRENT_LIST_DIR}/pong_ve.c
)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}/../src)

ADD_EXECUTABLE			(ping_vh ${VH_SRC})
TARGET_LINK_LIBRARIES	(ping_vh urpcVH pthread)
#INSTALL					(TARGETS ping_vh RUNTIME DESTINATION tests)

ADD_SUBDIRECTORY(ve)