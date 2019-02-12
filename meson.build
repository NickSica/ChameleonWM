
project(
    'chameleonwm',
    'cpp',
    'c',
    version: '0.0.1',
    license: 'MIT',
    meson_version: '>=0.43.0',
    default_options: [
	    'cpp_std=c++17',
	    'warning_level=2',
	    'werror=true',
	    'buildtype=debug',
    ],
)

# Avoid wl_buffer deprecation warnings
add_project_arguments(
    '-Wno-unused-parameter',
    '-Wextra',
    '-DWLR_USE_UNSTABLE',
    language: ['cpp', 'c']
)

if(get_option('buildtype') == 'release')
    add_project_arguments('-D_FORTIFY_SOURCE=2', language: ['cpp', 'c'])
endif

inc_folder = include_directories('include')


wlroots	       = dependency('wlroots')
wayland_server = dependency('wayland-server')
wayland_client = dependency('wayland-client')
wayland_protos = dependency('wayland-protocols', version: '>=1.12')
pixman	       = dependency('pixman-1')
xkbcommon      = dependency('xkbcommon')

subdir('protocol')
subdir('src')
