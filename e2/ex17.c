#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
	int id;
	int set;
	char *name;
	char *email;
};

struct Database {
	struct Address *rows;
	int max_rows;
	int max_data;
};

struct Connection  {
	FILE *file;
	struct Database *db;
};

void Database_close(struct Connection *conn){
	if(conn){
		if(conn->file) fclose(conn->file);
		if(conn->db) free(conn->db);
		free(conn);
	}
}

void die(const char *message, struct Connection *conn) {
	Database_close(conn);
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

void Address_print(struct Address *addr){
	printf("%d %s %s\n",
		addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn){
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1) die("Failed to load database", conn);
}

struct Connection *Database_open(const char *filename, char mode){
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn) die("Memory Error!", conn);

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db) die("Memory Error!", conn);


	//If modal check
	if(mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");

		if(conn->file) {
			Database_load(conn);
		}
	}

	if(!conn->file) die("Failed to open File!", conn);

	return conn;
}

void Database_write(struct Connection *conn){
	rewind(conn->file);

	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1) die("Failed to write to the database", conn);

	rc = fflush(conn->file);
	if(rc == -1) die("Cannot Flush Database!", conn);

}

void Database_create(struct Connection *conn, int MAX_ROWS, int MAX_DATA){
	int i = 0;

	for(i = 0; i < MAX_ROWS; i++){
		// make and initialize a prototype
		struct Address addr = {.id = i, .set = 0};
		// Then just assign it!
		conn->db->rows[i] = addr;
	}

	conn->db->max_rows = MAX_ROWS;
	conn->db->max_data = MAX_DATA;

}

void Database_set(struct Connection *conn, int id, const char *name, const char *email) {
	struct Address *addr = &conn->db->rows[id];
	if(addr->set) die("ALReADY SET YOU DORK!, delete it first", conn);

	addr->set = 1;

	//Warning: bug, read the "How to break it and fix this!";
	char *res = strncpy(addr->name, name, conn->db->max_data);
	//demonstrate this bug
	if(!res) die("Name copy failed!", conn);

	res = strncpy(addr->email, email, conn->db->max_data);
	if(!res) die("Email copy failed!", conn);
}

void Database_get(struct Connection *conn, int id){
	struct Address *addr = &conn->db->rows[id];

	if(addr->set) {
		Address_print(addr);
	} else {
		die("ID IS NOT SET!", conn);
	}
}

void Database_delete(struct Connection *conn, int id){
	struct Address addr = {.id = id, .set = 0};
	conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn) {
	int i = 0;
	struct Database *db = conn->db;

	for(i = 0; i < conn->db->max_rows; i++) {
		struct Address *cur = &db->rows[i];

		if(cur->set) {
			Address_print(cur);
		}
	}
}

int main(int argc, char *argv[]) {
	if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

	char *filename = argv[1];
	char action = argv[2][0];

	struct Connection *conn = Database_open(filename, action);
	int id = 0;

	if(action != 'c'){
		if (argc > 3) id = atoi(argv[3]);
		if (id >= conn->db->max_rows) die("There's not that many records!!", conn);
	}	

	switch(action) {
		case 'c':
			if(argc != 5) die("You neex a MAX_ROWS value and a MAX_DATA value!", conn);

			int m_rows = atoi(argv[3]);
			int m_data = atoi(argv[4]);

			Database_create(conn, m_rows, m_data);
			Database_write(conn);
			break;

		case 'g':
			if(argc != 4) die("You need an ID to get!", conn);

			Database_get(conn, id);
			break;

		case 's':
			if(argc != 6) die("Need id, name, email to set", conn);

			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;

		case 'd':
			if(argc != 4) die("Need id to delete!", conn);

			Database_delete(conn, id);
			Database_write(conn);
			break;

		case 'l':
			Database_list(conn);
			break;
		default:
			die("Invalid option! only; c=create, g=get, s=set, d=delete, l=list", conn);
	}


	Database_close(conn);

	return 0;
}