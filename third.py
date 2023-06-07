import psycopg2
import json

"""
 use the psycopg2 module, which is a PostgreSQL
  database adapter for Python. It provides a way
   to connect to a PostgreSQL database and execute
  SQL commands using Python.
"""

# Connect to the PostgreSQL database
conn = psycopg2.connect(
    host="your_host",
    database="your_database",
    user="your_username",
    password="your_password"
)

# Create a cursor object to execute SQL commands
cur = conn.cursor()

# Execute a SELECT query
cur.execute("SELECT * FROM public.user_table")

# Fetch all rows from the query result
rows = cur.fetchall()

# Convert the query result to a list of dictionaries
data = []
for row in rows:
    data.append({
        "user_id": row[0],
        "name": row[1],
        "age": row[2],
        "phone": row[3]
    })

# Convert the list of dictionaries to a JSON string
json_data = json.dumps({
    "status_code": 200,
    "data": data
})

# Close the cursor and connection
cur.close()
conn.close()

# Print the JSON string
print(json_data)
