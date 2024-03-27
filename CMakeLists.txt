cmake_minimum_required(VERSION 3.0)

project(getSymbol)

add_library(getSymbol SHARED "getSymbol.cpp")

find_package(DynamoRIO)
configure_DynamoRIO_client(getSymbol)

use_DynamoRIO_extension(getSymbol drmgr)
use_DynamoRIO_extension(getSymbol drx)
use_DynamoRIO_extension(getSymbol drsyms)
use_DynamoRIO_extension(getSymbol drwrap)
use_DynamoRIO_extension(getSymbol drreg)
use_DynamoRIO_extension(getSymbol droption)