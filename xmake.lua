add_rules('mode.debug', 'mode.release')

set_allowedplats('windows')
set_allowedarchs('windows|x64')

set_runtimes('MT')

-- set_warnings('all', 'extra')
set_warnings('none')
set_languages('c++14')

add_defines('_LARGE_WORLDS', '_DEBUG_MENUS_ENABLED')

if is_mode('debug') then
    -- never defines _DEBUG; we do not use the debug CRT (under Windows).
    add_defines('MINECRAFT_DEBUG')
end

if is_plat('windows') then
    add_defines('_CRT_NON_CONFORMING_SWPRINTFS', '_CRT_SECURE_NO_WARNINGS')
    add_defines('_WINDOWS64')
end

target('client')
    set_kind('binary')
    add_files(
        'src/**.cpp',
        'src/**.c' -- TODO: RM THIS. (zlib)
    )
    add_links(
        '4J_Render_PC',
        '4J_Storage',
        '4J_Input',
        'mss64',
        'iggy_w64',
        '/usr/lib/wine/x86_64-windows/libxinput.a' -- TODO: RM THIS.
    )
    add_syslinks('user32', 'd3d11', 'legacy_stdio_definitions')
    add_linkdirs(
        'src/deps/4jlibs/libs',
        'src/deps/mss/lib',
        'src/deps/iggy/lib'
    )
    add_includedirs(
        'src',
        'src/deps/4jlibs/inc',
        'src/deps/iggy/include',
        'src/deps/iggy/gdraw',
        'src/deps/mss/include',
        'src/deps/xml',
        'src/deps/zlib'
    )
