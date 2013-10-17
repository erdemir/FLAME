#include "header.h"
#include "household_agent_header.h"


/*
 * \fn: int household_init_post_id()
 * \brief:
 */
int household_init_post_id()
{
    add_household_jpoffice_id_message(ID);
    
	return 0; /* Returning zero means the agent is not removed */
}

/*
 * \fn: int household_init_employment()
 * \brief:
 */
int household_init_employment()
{
    START_JPOFFICE_HOUSEHOLD_EMPLOYER_MESSAGE_LOOP
    MY_EMPLOYER_ID = jpoffice_household_employer_message->employer_id;
    FINISH_JPOFFICE_HOUSEHOLD_EMPLOYER_MESSAGE_LOOP
    
	return 0; /* Returning zero means the agent is not removed */
}


/*
 * \fn: int household_init_balancesheet()
 * \brief: 
 */
int household_init_balancesheet()
{
    /* The firms are initiliazed loans only with their preferred banks.
     */
    add_household_bank_init_mortgages_message(BANK_ID, MORTGAGES);
    add_household_bank_init_deposit_message(BANK_ID, LIQUIDITY);
	return 0; /* Returning zero means the agent is not removed */
}

/*
 * \fn: int household_iterate()
 * \brief: Resumes its regular functions.
 */
int household_iterate()
{
    if (DATA_COLLECTION_MODE) {
        char * filename;
        FILE * file1;
        
        /* @\fn: int household_consumption_recieve_goods() */
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "./outputs/data/Household_Weekly.txt");
        file1 = fopen(filename,"a");
        fprintf(file1,"%s %s %s %s %s %s\n","IT_NO", "ID", "LIQUIDITY", "WEEKLY_CONSUMPTION_BUDGET", "money_to_spend", "money_spent");
        fprintf(file1,"%d %d %f %f %f %f\n",IT_NO, ID, LIQUIDITY, WEEKLY_CONSUMPTION_BUDGET, 0.0, 0.0);
        fclose(file1);
        
        /* @\fn: household_housing_debt_writeoff() */
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "./outputs/data/Household_Monthly_FirstDay.txt");
        file1 = fopen(filename,"a");
        fprintf(file1,"%s %s %s %s %s %s %s %s\n", "IT_NO", "ID", "MORTGAGES", "MORTGAGE_COST", "HOUSING_UNITS", "HOUSING_VALUE", "EQUITY_RATIO", "LIQUIDITY");
        double mcost = MORTGAGE_COSTS[0];
        fprintf(file1,"%d %d %f %f %d %f %f %f\n",IT_NO, ID, MORTGAGES, mcost, HOUSING_UNITS, HOUSING_VALUE, EQUITY_RATIO, LIQUIDITY);
        fclose(file1);
        
        /* @\fn: int household_credit_collect_benefits() */
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "./outputs/data/Household_Monthly_LastDay.txt");
        file1 = fopen(filename,"a");
        fprintf(file1,"%s %s %s %s %s %s\n","IT_NO", "ID", "MY_EMPLOYER_ID", "WAGE", "unemployment_benefit", "general_benefit");
        fprintf(file1,"%d %d %d %f %f %f\n",IT_NO, ID, MY_EMPLOYER_ID, WAGE, 0.0, 0.0);
        fclose(file1);
        
        /* @\fn: int household_credit_do_balance_sheet() */
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "./outputs/data/Household_Quarterly.txt");
        file1 = fopen(filename,"a");
        fprintf(file1,"%s %s %s %s %s %s %s %s %s\n","IT_NO", "ID", "TOTAL_ASSETS", "LIQUIDITY", "HOUSING_VALUE", "CAPITAL_INCOME", "MORTGAGES", "HOUSING_PAYMENT", "EQUITY");
        fprintf(file1,"%d %d %f %f %f %f %f %f %f\n",IT_NO, ID, TOTAL_ASSETS, LIQUIDITY, HOUSING_VALUE, CAPITAL_INCOME, MORTGAGES, HOUSING_PAYMENT, EQUITY);
        fclose(file1);
        
        free(filename);
    }
    
    IT_NO++;
	return 0; /* Returning zero means the agent is not removed */
}

/*
 * \fn: int household_update_bank_account()
 * \brief: puts money to deposit account of its prefered bak. */
int household_update_bank_account()
{
    if (LIQUIDITY > 0) {
        add_household_bank_update_deposit_message(BANK_ID, LIQUIDITY);
    }
    
	return 0; /* Returning zero means the agent is not removed */
}