qt6_rcc = find_program('rcc', required: true)

qt_resource = custom_target('qt_resource',
  input: 'resources.qrc',
  output: 'qrc_resources.cpp',
  command: [qt6_rcc, '-o', '@OUTPUT@', '@INPUT@']
)

# Install the resource file if needed
install_data('../assets/hello.png', install_dir: get_option('prefix') / 'share' / meson.project_name() / 'images')
