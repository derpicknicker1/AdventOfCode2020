/*

*/
#include "advent.h"

typedef struct {
	int nonterminal;
	char terminal;
	int left;
	int right;
} Rule;

typedef struct Node {
	Rule *rule;
	struct Node *next;
} Node;


int cyk(char* pattern, Node* rules, int num_symbols) {
	int (*matches)[strlen(pattern) + 1][num_symbols] = calloc(strlen(pattern) + 1, sizeof(*matches));

	char *left = calloc(100, sizeof(char));
	char *right = calloc(100, sizeof(char));

	int s;
	Node *iter;
	for (s = 0; s < strlen(pattern); s++)
		for (iter = rules; iter && iter->rule; iter = iter->next)
			if (iter->rule->terminal == pattern[s])
				matches[1][s + 1][iter->rule->nonterminal] = 1;


	int l, p;
	for (l = 2; l <= strlen(pattern); l++)
		for (s = 1; s <= strlen(pattern) - l + 1; s++)
			for (p = 1; p <= l - 1; p++)
				for (iter = rules; iter && iter->rule; iter = iter->next) {
					Rule *rule = iter->rule;
					if (!rule->terminal) {
						int left_matches = matches[p][s][rule->left];
						int right_matches = matches[l - p][s + p][rule->right];

						if (left_matches && right_matches) {
							memcpy(left, pattern + s - 1, p);
							memcpy(right, pattern + s - 1 + p, l - p);
							matches[l][s][rule->nonterminal] = left_matches && right_matches;
							memset(left, 0, 100);
							memset(right, 0, 100);
						}
					}
				}

	int good = matches[strlen(pattern)][1][0];
	free(left);
	free(right);
	free(matches);
	return good;
}

/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	FILE* in = fopen(f, "r");

	Node *rules = malloc(sizeof(Node));
	Node *tail = rules;

	char* line = calloc(100, sizeof(char));
	char* token = calloc(10, sizeof(char));
	char* subtoken = calloc(10, sizeof(char));
	char* saveptr;
	char* msaveptr;

	int num_symbols = 0;

	// Parse the rules.
	while (fgets(line, 100, in)) {
		if (strchr(line, ':')) {
			token = strtok_r(line, " :", &saveptr);
			int nonterminal = atoi(token);
			if (nonterminal > num_symbols) {
				num_symbols = nonterminal;
			}
			while ((token = strtok_r(NULL, "|", &saveptr))) {
				int left = -1;
				int right = -1;
				char terminal = 0;
				subtoken = strtok_r(token, " ", &msaveptr);
				if (subtoken[0] == '"') {
					terminal = subtoken[1];
					left = 0;
					right = 0;
				} else {
					left = atoi(subtoken);
					subtoken = strtok_r(NULL, " ", &msaveptr);
					right = subtoken?atoi(subtoken):-1;

				}
				Rule *rule = malloc(sizeof(Rule));
				rule->nonterminal = nonterminal;
				rule->left = left;
				rule->right = right;
				rule->terminal = terminal;
				tail->rule = rule;

				Node *next = malloc(sizeof(Node));
				tail->next = next;
				tail = tail->next;

			}
		}
	}

	// Remove unitary rules.
	// (There are no other non-CNF rules. I looked.)
	Node *iter;
	Node *subiter;
	Node *newrules = malloc(sizeof(Node));
	Node *newtail = newrules;
	for (iter = rules; iter && iter->rule; iter = iter->next) {
		Rule *rule = iter->rule;
		if (rule->right == -1) {
			for (subiter = rules; subiter && subiter->rule; subiter = subiter->next) {
				Rule *subrule = subiter->rule;
				if (subrule->nonterminal == rule->left) {
					Rule *newrule = malloc(sizeof(Rule));
					newrule->nonterminal = rule->nonterminal;
					newrule->left = subrule->left;
					newrule->right = subrule->right;
					newrule->terminal = subrule->terminal;

					newtail->rule = newrule;
					Node *next = malloc(sizeof(Node));
					newtail->next = next;
					newtail = newtail->next;
				}
			}
		}
	}

	for (iter = newrules; iter && iter->rule; iter = iter->next) {
		Rule *newrule = iter->rule;
		tail->rule = newrule;
		tail->next = malloc(sizeof(Node));
		tail = tail->next;
	}

	int i;
	for (i = 0; i < 3; i++) {
		for (iter = rules; iter; iter = iter->next) {
			if (iter->rule && iter->rule->right == -1) {
				Node *next = iter->next;
				iter->rule = next->rule;
				iter->next = next->next;
				free(next);
			}
		}
	}

	rewind(in);
	char *sline = calloc(100, sizeof(char));
	int total = 0;
	while (fgets(line, 100, in)) {
		sline = strtok(line, "\n");
		if (sline && !strchr(sline, ':')) 
			if ( cyk(sline , rules, num_symbols + 1) )
				total++;
	}

	printf("TOTAL %d\n", total);

	free(rules);
	free(token);
	free(line);
	fclose(in);
}

/*##########################
# Function to solve part A #
##########################*/
void get19a(char * f) {
	if(!getInput(f))
		return;
	
	int result = 0;
	
	printf("19a: %d\n", result);
}

/*##########################
# Function to solve part B #
##########################*/
void get19b(char *f) {
	/*if(!getInput(f))
		return;*/

	int result = 0;

	printf("19b: %d\n\n", result);
}
