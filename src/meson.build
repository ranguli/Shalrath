subdir('UI')
subdir('Network')
subdir('Database')
subdir('Model')
subdir('Parser')

executable('shalrath',
  sources: [
    'main.cpp'
  ],
  dependencies: [qt6_dep, ui_dep, network_dep, database_dep, parser_dep],
  install: true
)
