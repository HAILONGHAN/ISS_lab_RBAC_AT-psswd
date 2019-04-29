#include"rbac.cpp"

int main() {

	// U R P 分别为用户集合，角色集合，权限集合
	power_table P;
	role_table R;
	object_table U;

	//PAR UAR 分别表示许可权与角色之间多对多的指派关系，用户与角色之间多对多的指派关系。
	role_power_table PAR;
	object_role_table UAR;

	char command[20];
	cout << "Welcome here" << endl;
	cout << "You are a manager of this system!" << endl;
	while (1) {
		cout << "Please choose your operation:" << endl;
		cout << "1.add power\n2.add role\n3.add user\n4.add role_power\n5.add user_role\0.exit" << endl;
		cin >> command;
		if (command[0] == '0')
			break;
		switch (command[0]) {
		case '1':
			unsigned int short id;
			cout << "ID:";
			cin >> id;
			cout << "NAME:";
			cin >> command;
			P.add_power(id, command);
			break;
		case '2':
			unsigned int short id;
			cout << "ID:";
			cin >> id;
			cout << "NAME:";
			cin >> command;
			P.add_power(id, command);
			break;
		case '3':
			unsigned int short id;
			cout << "ID:";
			cin >> id;
			cout << "NAME:";
			cin >> command;
			P.add_power(id, command);
			break;
		case '4':
			unsigned int short r_id;
			unsigned int short p_id;
			cout << "ROLE ID:";
			cin >> r_id;
			cout << "POWER ID:";
			cin >> p_id;
			if (R.if_in(r_id) && P.if_in(p_id)) {
				PAR.add_role_power(R.id_to_name(r_id), P.id_to_name(p_id));
			}
			break;
		case '5':
			unsigned int short u_id;
			unsigned int short r_id;
			cout << "ROLE ID:";
			cin >> r_id;
			cout << "USER ID:";
			cin >> u_id;
			if (R.if_in(r_id) && U.if_in(u_id)) {
				UAR.add_object_role(R.id_to_name(r_id), U.id_to_name(u_id));
			}
			break;
		default:
			break;
		}
	}
	while (1) {
		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
		cout << "^^^^^^^^^^WELCOME INTO SYSTEM^^^^^^^^^^^^^" << endl;
		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" << endl;
		cout << "You need to LOGIN\n" << endl;
		cout << "ID:";
		unsigned int short id;
		cin >> id;
		cout << "Password(default 0):";
		cin >> command;
		if (!U.login(id, command)) {
			break;
		}
		cout << "Login success!!!" << endl;
		while (1) {
			cout<<"\nPlease choose your work:\n0:read the resource\n1:execute the resource\n2:new the resource\n3:delete the resource \n4:change the resource \n5:exit"<<endl;
			fflush(stdin);
			cin>>command;
			if (command[0] == '5') {
				break;
			}

			//简单版本，更具有灵活性
			/**********************************************

			cout << "Please INPUT your operation:";
			cin >> command;
			if (UAR.if_has_power(U.id_to_name(id), "READ", PAR)) {
				cout << "OK" << endl;
			}
			cout << "You are not permitted!" << endl;

			**********************************************/
			

			switch (command[0]) {
			case '0':
				if (!UAR.if_has_power(U.id_to_name(id),"READ",PAR)) {
					cout<<"You are not permitted!"<<endl;
					break;
				}
				cout<<"OK"<<endl;
				break;
			case '1':
				if (!UAR.if_has_power(U.id_to_name(id), "EXEC", PAR)) {
					cout << "You are not permitted!" << endl;
					break;
				}
				cout << "OK" << endl;
				break;
			case '2':
				if (!UAR.if_has_power(U.id_to_name(id), "NEW", PAR)) {
					cout << "You are not permitted!" << endl;
					break;
				}
				cout << "OK" << endl;
				break;
			case '3':
				if (!UAR.if_has_power(U.id_to_name(id), "DEL", PAR)) {
					cout << "You are not permitted!" << endl;
					break;
				}
				cout << "OK" << endl;
				break;
			case '4':
				if (!UAR.if_has_power(U.id_to_name(id), "CHANGE", PAR)) {
					cout << "You are not permitted!" << endl;
					break;
				}
				cout << "OK" << endl;
				break;
			case '5':
				if (!UAR.if_has_power(U.id_to_name(id), "ONLY", PAR)) {
					cout << "You are not permitted!" << endl;
					break;
				}
				cout << "OK" << endl;
				break;
			default:
				break;
			}
		}
		break;
	}
	return 0;
}