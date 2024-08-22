

CREATE TABLE IF NOT EXISTS `settings` (
  `id` INTEGER PRIMARY KEY,
  `key` varchar(255) NOT NULL UNIQUE,
  `value` text NOT NULL
);

CREATE TABLE IF NOT EXISTS `source_types` (
  `id` INTEGER PRIMARY KEY,
  `name` varchar(255) NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS `source` (
  `id` INTEGER PRIMARY KEY,
  `name` varchar(255) NOT NULL UNIQUE,
  `url` varchar(255) NOT NULL UNIQUE,
  `source_type_id` INTEGER NOT NULL,
  `filter` varchar(255) DEFAULT NULL,
  FOREIGN KEY(source_type_id) REFERENCES source_types(id)
);

CREATE TABLE IF NOT EXISTS `articles` (
  `id` INTEGER NOT NULL,
  `datetime` INTEGER NOT NULL,
  `text` text NOT NULL,
  `source_id` INTEGER NOT NULL,
  `link` varchar(255) NOT NULL,
  `reply_to_id` INTEGER DEFAULT NULL,
  `images_attached` TINYINT DEFAULT FALSE,
  FOREIGN KEY(source_id) REFERENCES source(id),
  PRIMARY KEY(id, source_id)
);

CREATE TABLE IF NOT EXISTS `images` (
  `image_id` INTEGER PRIMARY KEY,
  `article_id` INTEGER NOT NULL,
  `data` BLOB,
  FOREIGN KEY(article_id) REFERENCES articles(id)
);

