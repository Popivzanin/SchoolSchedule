
CREATE TABLE AppUser (
    id          INTEGER PRIMARY KEY,
    username    VARCHAR UNIQUE,
    email       VARCHAR UNIQUE,
    password    VARCHAR,
    role        VARCHAR
);

INSERT INTO AppUser
(username, email, password, role) VALUES ('admin', 'admin@domain.com', 'admin', 'ROLE_ADMIN');

CREATE TABLE Subjects (
    subject_id      INTEGER PRIMARY KEY,
    subject_name    VARCHAR UNIQUE
);

CREATE TABLE Schedule (
    schedule_id INTEGER PRIMARY KEY,
    class_name VARCHAR,
    subjects VARCHAR,
    week_day VARCHAR
);

