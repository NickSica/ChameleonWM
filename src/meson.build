wm_src = files(
	'main.cpp',
	'keyboard.cpp',
	'server.cpp',
)

wm_deps = [
    wayland_server,
    wlroots,
    pixman,
    xkbcommon
]

executable(
    'chameleonwm',
    sources: wm_src,
    include_directories: [inc_folder],
    dependencies: [wm_deps, wlr_protos],
    # install: true
)