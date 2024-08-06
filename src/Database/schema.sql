CREATE TABLE maps (
    map_id TEXT PRIMARY KEY,
    type INTEGER,
    rating INTEGER,
    normalized_users_rating REAL,
    author TEXT,
    title TEXT,
    md5sum TEXT,
    size INTEGER,
    date TEXT,
    description TEXT,
    zipbasedir TEXT,
    commandline TEXT,
    startmap TEXT,
    thumbnail BLOB
);

CREATE TABLE tags (
    tag TEXT PRIMARY KEY
);

CREATE TABLE map_tags (
    map_id TEXT,
    tag TEXT,
    FOREIGN KEY(map_id) REFERENCES maps(map_id),
    FOREIGN KEY(tag) REFERENCES tags(tag),
    PRIMARY KEY(map_id, tag)
);

CREATE TABLE user_downloads (
    user_id TEXT,
    map_id TEXT,
    downloaded BOOLEAN,
    FOREIGN KEY(map_id) REFERENCES maps(map_id),
    PRIMARY KEY(user_id, map_id)
);

CREATE TABLE user_favorites (
    user_id TEXT,
    map_id TEXT,
    favorited BOOLEAN,
    FOREIGN KEY(map_id) REFERENCES maps(map_id),
    PRIMARY KEY(user_id, map_id)
);

CREATE TABLE user_map_stats (
    user_id TEXT,
    map_id TEXT,
    played BOOLEAN,
    play_count INTEGER,
    total_play_time INTEGER,
    last_played TEXT,
    FOREIGN KEY(map_id) REFERENCES maps(map_id),
    PRIMARY KEY(user_id, map_id)
);

CREATE TABLE user_quake_configs (
    user_id TEXT,
    config_id INTEGER PRIMARY KEY AUTOINCREMENT,
    quake_directory TEXT,
    quake_executable TEXT,
    extra_commandline_options TEXT
);
