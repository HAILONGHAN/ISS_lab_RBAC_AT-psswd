#include<iostream>
#include<cstring>

using namespace std;

//权限原子
struct power {
	unsigned int short power_id;
	string power_name;
	struct power * power_next;
};

//角色原子
struct role {
	unsigned int short role_id;
	string role_name;
	struct role * role_next;
};

//用户原子
struct object{
	unsigned int short o_id;
	string o_name;
	string o_passwd;
	struct object *object_next;
};

//权限集合
class power_table {
private:
	struct power * power_list;
	struct power * power_last;
public:
	power_table() {
		power_list = NULL;
	}
	void add_power(unsigned int short id,string name) {
		struct power* temp = power_list;
		while (temp != NULL) {
			if (id == temp->power_id) {
				cout << "ID is exist" << endl;
				return;
			}
			if (name == temp->power_name) {
				cout << "NAME is exist" << endl;
				return;
			}
			temp = temp->power_next;
		}
		temp = (struct power*)malloc(sizeof(struct power));
		temp->power_id = id;
		temp->power_name = name;
		temp->power_next = NULL;
	}
	bool if_in(unsigned int short id) {
		struct power * temp = power_last;
		while (temp != NULL) {
			if (temp->power_id == id) {
				return true;
			}
			temp = temp->power_next;
		}
		return false;
	}
	string id_to_name(unsigned int short id) {
		struct power * temp = power_list;
		while (temp != NULL) {
			if (temp->power_id == id) {
				return temp->power_name;
			}
			temp = temp->power_next;
		}
		return NULL;
	}

};

//角色集合
class role_table{
private:
	struct role * role_list;
public:
	role_table();
	void add_role(unsigned int short id, string name) {
		struct role* temp = role_list;
		while (temp!=NULL){
			if (id == temp->role_id){
				cout << "ID is exist" << endl;
				return;
			}
			if (name == temp->role_name) {
				cout << "NAME is exist" << endl;
				return;
			}
			temp = temp->role_next;
		}
		temp = (struct role*)malloc(sizeof(struct role));
		temp->role_id = id;
		temp->role_name = name;
		temp->role_next = NULL;
	}
	bool if_in(unsigned int short id) {
		struct role * temp = role_list;
		while (temp != NULL) {
			if (temp->role_id == id) {
				return true;
			}
			temp = temp->role_next;
		}
		return false;
	}

	string id_to_name(unsigned int short id) {
		struct role * temp = role_list;
		while (temp != NULL) {
			if (temp->role_id == id) {
				return temp->role_name;
			}
			temp = temp->role_next;
		}
		return NULL;

	}
};

role_table::role_table(){
	role_list = NULL;
}

//用户集合
class object_table{
private:
	struct object * object_list;
public:
	object_table();
	void add_object(unsigned int short id, string name) {
		struct object * temp = object_list;
		while (temp!=NULL){
			if (id == temp->o_id) {
				cout << "ID is exist" << endl;
				return;
			}
			if (name == temp->o_name) {
				cout << "NAME is exist" << endl;
				return;
			}
			temp = temp->object_next;
		}
		temp = (struct object*)malloc(sizeof(struct object));
		temp->o_id = id;
		temp->o_name = name;
		cout << "Please input your passwd:";
		cin.getline(temp->o_passwd);
		temp->object_next = NULL;
		return;
	}

	bool if_in(unsigned int short id) {
		struct object * temp = object_list;
		while (temp != NULL) {
			if (temp->o_id == id) {
				return true;
			}
			temp = temp->object_next;
		}
		return false;
	}

	bool login(unsigned int short id,string passwd) {
		struct object * temp = object_list;
		while (temp != NULL) {
			if (temp->o_id == id) {
				if (temp->o_passwd == passwd) {
					return true;
				}
				return false;
			}
			temp = temp->object_next;
		}
		return false;
	}

	string id_to_name(unsigned int short id) {
		struct object * temp = object_list;
		while (temp != NULL) {
			if (temp->o_id == id) {
				return temp->o_name;
			}
			temp = temp->object_next;
		}
		return NULL;
	}


};

object_table::object_table(){
	object_list = NULL;
}

//角色权限授权原子
struct role_power {
	string role_name;
	string power_name;
	struct role_power* role_power_next;
};

//用户角色授权原子
struct object_role {
	string o_name;
	string role_name;
	struct object_role * o_role_next;
};

//角色权限授权表
class role_power_table {
private:
	struct role_power* role_power_list;
public:
	role_power_table() {
		role_power_list = NULL;
	}
	void add_role_power(string role,string power) {
		struct role_power* temp = role_power_list;
		while (temp != NULL) {
			if (temp->role_name == role) {
				if (temp->power_name == power) {
					return;
				}
			}
			temp = role_power_list->role_power_next;
		}
		temp = (struct role_power*)malloc(sizeof(struct role_power));
		temp->role_name = role;
		temp->power_name = power;
		temp->role_power_next = NULL;
		return;
	}

	bool if_has_power(string role_name, string power_name) {
		struct role_power* temp = role_power_list;
		while (temp != NULL) {
			if (temp->role_name == role_name) {
				if (temp->power_name == power_name) {
					return true;
				}
			}
			temp = role_power_list->role_power_next;
		}
		return false;
	}
};

//用户角色授权表
class object_role_table {
private:
	struct object_role* object_role_list;
public:
	object_role_table() {
		object_role_list = NULL;
	}
	void add_object_role(string object ,string role) {
		struct object_role * temp = object_role_list;
		while (temp != NULL) {
			if (temp->o_name == object) {
				if (temp->role_name == role) {
					return;
				}
			}
			temp = temp->o_role_next;
		}
		temp = (struct object_role*)malloc(sizeof(struct object_role));
		temp->o_name = object;
		temp->role_name = role;
		temp->o_role_next = NULL;
		return;
	}

	bool if_has_power(string object_name, string power_name,role_power_table PAR) {
		struct object_role* temp =object_role_list;
		while (temp != NULL) {
			if (temp->o_name == object_name) {
				if (PAR.if_has_power(temp->role_name,power_name)) {
					return true;
				}
			}
			temp = object_role_list->o_role_next;
		}
		return false;
	}
};
