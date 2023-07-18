cmake_minimum_required(VERSION 3.10)

project(server LANGUAGES C VERSION 1.0)
add_executable(server server.c)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "AM")
INCLUDE(CPack)

