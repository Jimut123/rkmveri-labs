project('oglcs',
	['c', 'cpp'],
	version : '0.0.0',
	license : 'MIT',
	meson_version : '>= 0.44',
  	default_options : [
		'buildtype=release', 
		'c_std=c11', 
		'cpp_std=c++17', 
		'warning_level=3', 
		'werror=true',
		'layout=mirror'
	]
)

c_compiler = meson.get_compiler('c')
cpp_compiler = meson.get_compiler('cpp')

add_project_arguments('-Wno-unused-parameter', language: ['c', 'cpp'])
add_project_arguments('-Wno-unused-function', language: ['c', 'cpp'])
add_project_arguments('-Wno-unused-result', language: ['c', 'cpp'])

glfw_dep   = dependency('glfw3', version: '>= 3')
glew_dep   = dependency('glew')

m_dep = cpp_compiler.find_library('m', required : false)

gl_deps = [glfw_dep, glew_dep, m_dep]

subdir('src')
