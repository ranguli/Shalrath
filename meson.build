project('shalrath', 'cpp',
  default_options: ['cpp_std=c++17'])

qt6_dep = dependency('qt6', modules: ['Core', 'Gui', 'Widgets'])

qt6_rcc = find_program('rcc', required: true)

# Custom function to find moc
moc_paths = [
  '/usr/lib/qt6/libexec/moc',
  'moc',  # This will find moc in the system PATH
]

qt6_moc = []
foreach moc_path : moc_paths
  moc_candidate = find_program(moc_path, required: false)
  if moc_candidate.found()
    qt6_moc = moc_candidate
    break
  endif
endforeach

if qt6_moc.found() == false
  error('Qt 6 moc not found')
endif

qt_resource = custom_target('qt_resource',
  input: 'resources.qrc',
  output: 'qrc_resources.cpp',
  command: [qt6_rcc, '-o', '@OUTPUT@', '@INPUT@']
)

moc_files = [
  'src/MainWindow.h',
  'src/LeftPane.h',
  'src/RightPane.h'
]

moc_outputs = []
foreach moc_file : moc_files
  moc_basename = meson.project_name() + '_' + moc_file.split('/')[-1]
  moc_output = custom_target('moc_' + moc_basename,
    input: moc_file,
    output: 'moc_' + moc_basename + '.cpp',
    command: [qt6_moc, '@INPUT@', '-o', '@OUTPUT@']
  )
  moc_outputs += moc_output
endforeach

executable('shalrath',
  sources: ['src/main.cpp', 'src/MainWindow.cpp', 'src/LeftPane.cpp', 'src/RightPane.cpp', qt_resource] + moc_outputs,
  dependencies: [qt6_dep],
  install: true
)
