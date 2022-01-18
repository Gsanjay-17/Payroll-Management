#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define emp_file_name "employee_data.txt"


typedef struct
{
	int basic;
	int hra;
	int da;
	int ta;
	int ma;
	int gross;
	int epf;
	int tax;
	int net_pay;
}pay_struct;

typedef struct 
{
	char id[16];
	char name[40];
	char gender[8];
	int  age;
	int  basic_sal;
}emp_struct;

int add_employee();
int delete_employee();
int list_all_employee();
int generate_payroll();

int main()
{ 
	int option;
	int continue_program = 1;
	
	while(continue_program)
	{
		printf("\n\n 1. Add Employee \n");
		printf(" 2. Delete Employee \n");
		printf(" 3. List all employees \n");
		printf(" 4. Generate payrool \n");
		printf(" 5. Exit \n");
		
		printf("\nChoose one of the above options : ");
		scanf("%d", &option);
		
		switch (option)
		{
			case 1: 
				add_employee();
				break;
			
			case 2:
				delete_employee();
				break;
			
			case 3:
				list_all_employee();
				break;
			
			case 4:
				generate_payroll();
				break;
				
			case 5: 
				continue_program = 0;
				break;
				
			default: 
				printf("INVALID OPTION, Try Again !!! \n");
				break;
		}
	}
	
	return 0;
}
 
int add_employee()
{
	FILE *fp;
	emp_struct emp;
	int retVal = 0;
	
	fp = fopen(emp_file_name, "a+");
	if (fp != NULL)
	{
		printf("Enter Employee details !!\n");
		printf("Employee ID :");
		scanf("%s", emp.id);
		printf("Employee Name :");
		scanf("%s", emp.name);
		printf("Employee Gender :");
		scanf("%s", emp.gender);
		printf("Employee Age :");
		scanf("%d", &emp.age);
		printf("Basic Salary :");
		scanf("%d", &emp.basic_sal);
		
		fprintf(fp, "%8s %20s %7s %3d %7d\n", emp.id, emp.name, emp.gender, emp.age, emp.basic_sal);
		retVal = 1;
	}
	
	fclose(fp);
	return retVal;
}

int list_all_employee()
{
	int retVal = 0;
	int cnt = 0;
	FILE *fp;
	fp = fopen(emp_file_name, "r+");
	
	if (fp != NULL)
	{
		emp_struct emp;
		
		printf("========================================================\n");
		printf(" ID      NAME		      GENDER   AGE  BASIC SALARY \n");
		printf("========================================================\n");
		while (1)
		{
			fscanf(fp, "%s %s %s %d %d", emp.id, emp.name, emp.gender, &emp.age, &emp.basic_sal);
			if(feof(fp)) break;
			printf("%-8s %-20s %-7s %3d %7d \n", emp.id, emp.name, emp.gender, emp.age, emp.basic_sal);
		}
		
		printf("========================================================\n");
		retVal = 1;
		fclose(fp);
	}
	

	return retVal;
}

int generate_payroll()
{
	int retVal = 0;
	
	FILE *fp;
	fp = fopen(emp_file_name, "r+");
	if (fp != NULL)
	{
		emp_struct emp;
		pay_struct pay;
		int cnt = 0;
		
		printf("================================================================================================================\n");
		printf(" ID       NAME		      GENDER   AGE  BASIC   HRA     DA     TA     MA    GROSS   EPF    TAX    NET_SALARY \n");
		printf("================================================================================================================\n");
		while (1)
		{
			fscanf(fp, "%s %s %s %d %d", emp.id, emp.name, emp.gender, &emp.age, &emp.basic_sal);
			if(feof(fp)) break;
			
			pay.basic = emp.basic_sal;
			pay.hra = pay.basic * 25/100;
			pay.da = pay.basic * 20/100;
			pay.ta = 2000;
			pay.ma = 1500;
			pay.gross = pay.basic + pay.hra + pay.da + pay.ta + pay.ma ;
			pay.epf = pay.basic * 12/100;
			pay.tax = (pay.gross > 25000) ? (pay.gross * 20/100) : (pay.gross * 10/100);
			pay.net_pay = pay.gross - (pay.epf + pay.tax);
			printf("%-8s %-20s %-7s %3d %7d %6d %6d %6d %6d %7d %6d %6d %7d\n", emp.id, emp.name, emp.gender, emp.age, 
				pay.basic, pay.hra, pay.da, pay.ta, pay.ma, pay.gross, pay.epf, pay.tax, pay.net_pay);
		}
		printf("================================================================================================================\n\n");
		
		fclose(fp);
		retVal = 1;
	}
	

	return retVal;
}

int delete_employee()
{
	int retVal = 0;
	emp_struct emp[50]={0,};		
	char emp_id[16];
	FILE *fp;
	int cnt = 0, i = 0;
	
	fp = fopen(emp_file_name, "r");
	
	if (fp != NULL)
	{
		
		printf("Enter Employee ID to delete : ");
		scanf("%s", emp_id);
		
		while (1)
		{
			fscanf(fp, "%s %s %s %d %d", emp[i].id, emp[i].name, emp[i].gender, &emp[i].age, &emp[i].basic_sal);
			if(feof(fp)) break;
			
			
			if (strncmp(emp[i].id, emp_id, sizeof(emp_id)) == 0)
			{
				char delete_confirmation[8];
				printf("Are you sure to delete Employee %s ? (Yes/No): ", emp[i].name);
				
				scanf("%s", delete_confirmation);
				if ((strcmp(delete_confirmation, "YES") == 0 ) || (strcmp(delete_confirmation, "yes") == 0))
				{
					strcpy(emp[i].id, "");
					strcpy(emp[i].name, "");
					strcpy(emp[i].gender, "");
				}
				else 
					i++;
			}
			else
			{
				i++;
			}
		}
		fclose(fp);
	}
	
	
	cnt = i;
	fp = fopen(emp_file_name, "w+");
	if (fp != NULL)
	{
		for(i = 0; i < cnt; i++)
		{
			fprintf(fp, "%8s %20s %7s %3d %7d\n", emp[i].id, emp[i].name, emp[i].gender, emp[i].age, emp[i].basic_sal);
		}
		
		retVal=1;
		fclose(fp);
	}
	
	return retVal;
}