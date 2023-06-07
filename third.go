package main
/*
To use this driver, you need to have the libpq library installed on your system. You can install it using your system's package manager or download it from the PostgreSQL website.

Once you've installed the libpq library, save the above code into a file, e.g., `main.go`. Then, compile and run the code using the following commands:

go build -o pgjson main.go ./pgjson
This will connect to the PostgreSQL database and execute a SELECT query on the `public.user_table` table
The query result will be returned as a JSON string in the following format:

```json
{
  "status_code": 200,
  "data": [
    {
      "user_id": 1,
      "name": "John",
      "age": 28
    },
    {
      "user_id": 2,
      "name": "Tom",
      "age": 29,
      "phone": "1 800 123 1234"
    },
    {
      "user_id": 3,
      "name": "Jenny",
      "age": 34
    }
  ]
}
/*
#include <stdlib.h>
#include <libpq-fe.h>
*/
import "C"
import (
	"encoding/json"
	"unsafe"
)

type User struct {
	UserID int    `json:"user_id"`
	Name   string `json:"name"`
	Age    int    `json:"age"`
	Phone  string `json:"phone,omitempty"`
}

func main() {
	// Set up the libpq connection
	connInfo := C.CString("dbname=your_database user=your_username password=your_password")
	defer C.free(unsafe.Pointer(connInfo))
	conn := C.PQconnectdb(connInfo)
	defer C.PQfinish(conn)

	// Check for connection success
	if C.PQstatus(conn) != C.CONNECTION_OK {
		panic(C.GoString(C.PQerrorMessage(conn)))
	}

	// Prepare and execute the SELECT query
	query := C.CString("SELECT * FROM public.user_table")
	defer C.free(unsafe.Pointer(query))
	res := C.PQexec(conn, query)
	defer C.PQclear(res)

	// Check for query success
	if C.PQresultStatus(res) != C.PGRES_TUPLES_OK {
		panic(C.GoString(C.PQresultErrorMessage(res)))
	}

	// Parse the query result into a slice of User objects
	var users []User
	for row := 0; row < int(C.PQntuples(res)); row++ {
		user := User{
			UserID: int(C.atol(C.PQgetvalue(res, C.int(row), 0))),
			Name:   C.GoString(C.PQgetvalue(res, C.int(row), 1)),
			Age:    int(C.atol(C.PQgetvalue(res, C.int(row), 2))),
			Phone:  C.GoString(C.PQgetvalue(res, C.int(row), 3)),
	
		}
		users = append(users, user)
	}
	
	// Marshal the slice of User objects into a JSON string
	jsonData, err := json.Marshal(map[string]interface{}{
		"status_code": 200,
		"data":        users,
	})
	if err != nil {
		panic(err)
	}
	
	// Print the JSON string
	println(string(jsonData))