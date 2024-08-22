-- Database `gazeta`.
-- Used for application to store articles.

CREATE TABLE IF NOT EXISTS `settings` (
  `key` VARCHAR(255) PRIMARY KEY,
  `value` TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS `migrations` (
  `name` VARCHAR(255) PRIMARY KEY,
  `datetime_processed` TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS `source_types` (
  `id` INTEGER PRIMARY KEY,
  `name` VARCHAR(255) NOT NULL UNIQUE
);

INSERT OR REPLACE INTO `source_types` (`name`) VALUES ('telegram_web');

CREATE TABLE IF NOT EXISTS `source` (
  `id` INTEGER PRIMARY KEY,
  `name` VARCHAR(255) NOT NULL UNIQUE,
  `url` VARCHAR(255) NOT NULL UNIQUE,
  `source_type_id` INTEGER NOT NULL,
  `filter` VARCHAR(1024) DEFAULT NULL,
  `filter_startes_with` VARCHAR(255) DEFAULT NULL,
  FOREIGN KEY(source_type_id) REFERENCES source_types(id)
);

CREATE TABLE IF NOT EXISTS `articles` (
  `id` INTEGER NOT NULL,
  `datetime` TIMESTAMP NOT NULL,
  `text` TEXT NOT NULL,
  `source_id` INTEGER NOT NULL,
  `link` VARCHAR(255) NOT NULL,
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

