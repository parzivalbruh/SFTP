import sqlite3

db = "C:\\Users\\USER\\OneDrive\\Documents\\SFTP_project\\DB\\password_DB.db"
conn = sqlite3.connect(db)
cursor = conn.cursor()


def create_table(name, c1, c2, c3):
    try:
        create_table_sql = f"""
         CREATE TABLE IF NOT EXISTS {name} (
             {c1} TEXT PRIMARY KEY,
             {c2} TEXT,
             {c3} INT
         )
       """

        cursor.execute(create_table_sql)
        conn.commit()
        print(f"Table '{name}' created successfully.")

    except Exception as e:
        print(e)


def add_user(un, ph, per):

    if not cursor.execute("SELECT userName FROM PERMISSIONS WHERE userName = ?", (un,)).fetchone():
        cursor.execute("""
            INSERT INTO PERMISSIONS VALUES
                ('%s', '%s', %s)
        """ % (un, ph, per))
        conn.commit()
        print("person added")
    else:
        print("person is in table")


def ifExisted(c, d):
    command = f"SELECT {c} FROM PERMISSIONS WHERE {c} = ?"
    return cursor.execute(command, (d,)).fetchone()


def IsAuthorized(userName, password):
     if cursor.execute("SELECT userName FROM PERMISSIONS WHERE userName = ?", (userName,)).fetchone():
        print("exist")
        return (password == cursor.execute("SELECT passwordHash FROM PERMISSIONS WHERE userName = ?", (userName,)).fetchone()[0])