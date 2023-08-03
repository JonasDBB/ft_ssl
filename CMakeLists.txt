cmake_minimum_required(VERSION 3.23)
project(ft_ssl C)

set(CMAKE_C_STANDARD 99)

include(FetchContent)
FetchContent_Declare(
		ft_clib
		GIT_REPOSITORY https://github.com/JonasDBB/ft_clib.git
		GIT_TAG v1.3
)
FetchContent_MakeAvailable(ft_clib)

add_executable(ft_ssl)

add_subdirectory(src)

target_include_directories(ft_ssl PUBLIC inc)

target_compile_options(ft_ssl PUBLIC
		-Wall
		-Wextra
		-Werror
		-g3
		-fsanitize=address
		)

target_link_options(ft_ssl PUBLIC
		-fsanitize=address
		)

target_link_libraries(ft_ssl ft_clib ft_printf)