	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <time.h>
	#include <stdbool.h> 
	
	#define MAX_CANDIDATES 100
	#define MAX_VOTERS 100
	

	void voterFunction();
	void candidateFunction();
	void adminFunction();
	void createElectionSchedule();
	void candidateRegistration();
	void registerVoter();
	void updateVoterDetails();
	void deleteVoter();
	void searchVoterDetails();
	void deleteCandidate(const char *candidateName);
	void castVote();
	bool loadVotersFromFile(); 
	bool adminLogin(const char *userid, const char *password);
	

	int candidateCount = 0;
	int voterCount = 0;
	int serialCounter = 1000;

	struct Candidate {
	    char name[50];
	    char party[50];
	    char candidacyFrom[50];
	    int voteCount;
	};
	
	struct Voter {
	    int sno;
	    char password[50];
	    char name[50];
	    char dob[20];
	    char address[100];
	};
	
	

	struct Candidate candidates[MAX_CANDIDATES] = {0};
	struct Voter voters[MAX_VOTERS];
	
	
	int main() {
	    int choice;
	    printf("Welcome to the Voting System\n");
	    printf("Are you a:\n");
	    printf("1. Voter\n");
	    printf("2. Candidate\n");
	    printf("3. Admin\n");
	    printf("Enter your choice: ");
	    scanf("%d", &choice);
	
	    switch (choice) {
	        case 1:
	            voterFunction();
	            break;
	        case 2:
	            candidateFunction();
	            break;
	        case 3:
	            adminFunction();
	            break;
	        default:
	            printf("Invalid choice.\n");
	    }
	
	    return 0;
	}
	
	bool loadVotersFromFile() {
	    FILE *file = fopen("voterlist.txt", "r");
	
	    if (file == NULL) {
	        printf("Error opening file.\n");
	        return false;
	    }
	
	    while (fscanf(file, "%d,%49[^,],%49[^,],%19[^,],%99[^\n]", &voters[voterCount].sno, voters[voterCount].password, voters[voterCount].name, voters[voterCount].dob, voters[voterCount].address) == 5) {
	        voterCount++;
	    }
	
	    fclose(file);
	    return true;
	}
	
	

	bool voterLogin(int sno, const char *password) {
	    for (int i = 0; i < voterCount; i++) {
	        if (voters[i].sno == sno && strcmp(voters[i].password, password) == 0) {
	            printf("Login successful! Welcome, %s.\n", voters[i].name);
	            return true;
	        }
	    }
	    printf("Invalid serial number or password.\n");
	    return false;
	}
	
	void voterFunction() {
	    printf("Welcome Voter!\n");
	
	    char registered[4];
	    printf("Are you already registered as a voter? (yes/no): ");
	    scanf(" %3s", registered);
	
	    if (strcmp(registered, "yes") == 0) {
	        if (!loadVotersFromFile()) {
	            printf("Failed to load voter data.\n");
	            return;
	        }
	
	        int sno;
	        char password[50];
	        printf("Please enter your voter serial number: ");
	        scanf("%d", &sno);
	
	        printf("Please enter your password: ");
	        scanf(" %49[^\n]", password);
	        
	        if (!voterLogin(sno, password)) {
	            return;
	        }
	    } else if (strcmp(registered, "no") == 0) {
	        char registerChoice[4];
	        printf("Do you want to register as a voter? (yes/no): ");
	        scanf(" %3s", registerChoice);
	
	        if (strcmp(registerChoice, "yes") == 0) {
	            registerVoter();
	            return; 
	        } else if (strcmp(registerChoice, "no") == 0) {
	            printf("Okay, thank you.\n");
	        } else {
	            printf("Invalid choice.\n");
	        }
	    } else {
	        printf("Invalid choice.\n");
	        return; 
	    }
	

	    char voteChoice[4];
	    printf("Do you want to vote? (yes/no): ");
	    scanf(" %3s", voteChoice);
	
	    if (strcmp(voteChoice, "no") == 0) {
	        printf("Okay, thank you.\n");
	        return; 
	    } else if (strcmp(voteChoice, "yes") == 0) {
	        castVote(); 
	    } else {
	        printf("Invalid choice.\n");
	    }
	}
	
	void candidateFunction() {

	    char candidateId[50];
	    char password[50];
	
	    printf("Candidate Login\n");
	    printf("Enter candidate ID: ");
	    scanf("%s", candidateId);
	    printf("Enter password: ");
	    scanf("%s", password);
	
	 
	    if (strcmp(candidateId, "candidate1") == 0 && strcmp(password, "candidate123") == 0) {
	        printf("Login successful! Welcome Candidate.\n");
	

	        FILE *voteFile = fopen("votercount.txt", "r");
	        if (voteFile == NULL) {
	            printf("Error opening vote count file.\n");
	            return;
	        }
	
	        printf("Live Voting Results:\n");
	        char line[200];
	        while (fgets(line, sizeof(line), voteFile)) {
	            printf("%s", line);
	        }
	        fclose(voteFile);
	    } else {
	        printf("Invalid candidate ID or password.\n");
	    }
	}
	
	void adminFunction() {
	    printf("Admin Login\n");
	    char userid[50];
	    char password[50];
	    printf("Enter admin user ID: ");
	    scanf("%s", userid);
	    printf("Enter password: ");
	    scanf("%s", password);
	
	    if (!adminLogin(userid, password)) {
	        printf("Exiting admin panel.\n");
	        return;
	    }
	
	    int choice;
	    while (1) {
	        printf("\nVoting System Menu:\n");
	        printf("1. Create Election Schedule\n");
	        printf("2. Candidate Registration\n");
	        printf("3. Register Voter\n");
	        printf("4. Update Voter Details\n");
	        printf("5. Delete Voter\n");
	        printf("6. Search Voter Details\n");
	        printf("7. Cast Vote\n");
	        printf("8. Delete Candidate\n"); 
	        printf("9. Exit\n");
	        printf("Enter your choice: ");
	        scanf("%d", &choice);
	
	        switch (choice) {
	            case 1:
	                createElectionSchedule();
	                break;
	            case 2:
	                candidateRegistration();
	                break;
	            case 3:
	                registerVoter();
	                break;
	            case 4:
	                updateVoterDetails();
	                break;
	            case 5:
	                deleteVoter();
	                break;
	            case 6:
	                searchVoterDetails();
	                break;
	            case 7:
	                castVote();
	                break;
	            case 8:
	                char candidateName[50];
	                printf("Enter the name of the candidate to delete: ");
	                scanf("%s", candidateName);
	                deleteCandidate(candidateName);
	                break;
	            case 9:
	                printf("Exiting program.\n");
	                exit(0);
	            default:
	                printf("Invalid choice.\n");
	        }
	    }
	}
	
	bool adminLogin(const char *userid, const char *password) {
	    if (strcmp(userid, "admin") == 0 && strcmp(password, "admin123") == 0) {
	        printf("Admin login successful!\n");
	        return true;
	    } else {
	        printf("Invalid admin credentials.\n");
	        return false;
	    }
	}
	
	void createElectionSchedule() {
	    char schedule[100];
	    printf("Enter election schedule: ");
	    scanf(" %[^\n]s", schedule);
	
	    FILE *file = fopen("schedule.txt", "w");
	    if (file == NULL) {
	        printf("Error opening file.\n");
	        return;
	    }
	
	    fprintf(file, "%s\n", schedule);
	    fclose(file);
	    printf("Election schedule created successfully.\n");
	}
	
	void candidateRegistration() {
	    if (candidateCount >= MAX_CANDIDATES) {
	        printf("Maximum candidates reached.\n");
	        return;
	    }
	
	    printf("Enter candidate details:\n");
	    printf("Name: ");
	    scanf(" %[^\n]s", candidates[candidateCount].name);
	    printf("Party: ");
	    scanf(" %[^\n]s", candidates[candidateCount].party);
	    printf("Candidacy From: ");
	    scanf(" %[^\n]s", candidates[candidateCount].candidacyFrom);
	
	    candidateCount++;
	
	    FILE *file = fopen("candidate.txt", "a");
	    if (file == NULL) {
	        printf("Error opening file.\n");
	        return;
	    }
	
	    fprintf(file, "%s,%s,%s\n", candidates[candidateCount - 1].name,
	                                  candidates[candidateCount - 1].party,
	                                  candidates[candidateCount - 1].candidacyFrom);
	    fclose(file);
	    printf("Candidate registered successfully.\n");
	}
	
	void registerVoter() {
	    if (voterCount >= MAX_VOTERS) {
	        printf("Maximum voters reached.\n");
	        return;
	    }
	
	    struct Voter voter;
	    printf("Enter your details to register as a voter:\n");
	    printf("Name: ");
	    scanf(" %[^\n]", voter.name);
	    printf("Date of Birth (dd/mm/yyyy): ");
	    scanf(" %[^\n]", voter.dob);
	    printf("Address: ");
	    scanf(" %[^\n]", voter.address);
	

	    int year;
	    sscanf(voter.dob, "%*d/%*d/%d", &year);
	    int age = 2024 - year;
	
	    if (age < 18) {
	        printf("You must be at least 18 years old to register as a voter.\n");
	        return;
	    }
	

	    srand(time(NULL));
	    voter.sno = rand() % 1000 + 1000;
	

	    char password[7]; 
	    for (int i = 0; i < 6; ++i) {
	        password[i] = 'A' + rand() % 26; 
	    }
	    password[6] = '\0'; 
	
	    strcpy(voter.password, password); 
	
	    voters[voterCount++] = voter; 
	
	    FILE *file = fopen("voterlist.txt", "a");
	    if (file == NULL) {
	        printf("Error opening file.\n");
	        return;
	    }
	
	    fprintf(file, "%d,%s,%s,%s,%s\n", voter.sno, voter.password, voter.name,
	                                       voter.dob, voter.address);
	    fclose(file);
	    printf("You have been successfully registered as a voter.\n");
	    printf("Your voter serial number: %d\n", voter.sno);
	    printf("Your password: %s\n", voter.password);
	}
	
	
	void updateVoterDetails() {
	    int sno;
	    printf("Enter voter serial number to update details: ");
	    scanf("%d", &sno);
	
	    int found = 0;
	    for (int i = 0; i < voterCount; i++) {
	        if (voters[i].sno == sno) {
	            printf("Enter new details:\n");
	            printf("Name: ");
	            scanf(" %[^\n]s", voters[i].name);
	            printf("Date of Birth (dd/mm/yyyy): ");
	            scanf(" %[^\n]s", voters[i].dob);
	            printf("Address: ");
	            scanf(" %[^\n]s", voters[i].address);
	
	            found = 1;
	            break;
	        }
	    }
	
	    if (!found) {
	        printf("Voter not found.\n");
	    } else {
	        FILE *file = fopen("voterlist.txt", "w");
	        if (file == NULL) {
	            printf("Error opening file.\n");
	            return;
	        }
	
	        for (int i = 0; i < voterCount; i++) {
	            fprintf(file, "%d,%s,%s,%s,%s\n", voters[i].sno, voters[i].password,
	                                               voters[i].name, voters[i].dob,
	                                               voters[i].address);
	        }
	        fclose(file);
	        printf("Voter details updated successfully.\n");
	    }
	}
	
	void deleteVoter() {
	    int sno;
	    printf("Enter voter serial number to delete: ");
	    scanf("%d", &sno);
	
	    int found = 0;
	    for (int i = 0; i < voterCount; i++) {
	        if (voters[i].sno == sno) {
	            for (int j = i; j < voterCount - 1; j++) {
	                voters[j] = voters[j + 1];
	            }
	            found = 1;
	            break;
	        }
	    }
	
	    if (!found) {
	        printf("Voter not found.\n");
	    } else {
	        FILE *file = fopen("voterlist.txt", "w");
	        if (file == NULL) {
	            printf("Error opening file.\n");
	            return;
	        }
	
	        for (int i = 0; i < voterCount - 1; i++) {
	            fprintf(file, "%d,%s,%s,%s,%s\n", voters[i].sno, voters[i].password,
	                                               voters[i].name, voters[i].dob,
	                                               voters[i].address);
	        }
	        fclose(file);
	        voterCount--;
	        printf("Voter deleted successfully.\n");
	    }
	}
	
	void deleteCandidate(const char *candidateName) {

	    FILE *inputFile = fopen("cansidate.txt", "r");
	    if (inputFile == NULL) {
	        printf("Error opening candidate.txt for reading.\n");
	        return;
	    }
	
	
	    FILE *tempFile = fopen("temp.txt", "w");
	    if (tempFile == NULL) {
	        printf("Error creating temporary file.\n");
	        fclose(inputFile);
	        return;
	    }
	
	    char name[50], party[50], candidacyFrom[50];
	
	    // Read each line from the input file
	    while (fscanf(inputFile, "%49[^,],%49[^,],%49[^,]\n", name, party, candidacyFrom) == 3) {
	        // Check if the current candidate's name matches the one to delete
	        if (strcmp(name, candidateName) != 0) {
	            // Write the candidate details to the temporary file
	            fprintf(tempFile, "%s,%s,%s\n", name, party, candidacyFrom);
	        }
	    }
	
	    // Close both files
	    fclose(inputFile);
	    fclose(tempFile);
	
	    // Remove the original file
	    remove("candidate.txt");
	
	    // Rename the temporary file to the original name
	    if (rename("temp.txt", "candidate.txt") != 0) {
	        printf("Error renaming file.\n");
	    } else {
	        printf("Candidate '%s' deleted successfully.\n", candidateName);
	    }
	}
	
	void searchVoterDetails() {
	    int sno;
	    printf("Enter voter serial number to search details: ");
	    scanf("%d", &sno);
	
	    int found = 0;
	    for (int i = 0; i < voterCount; i++) {
	        if (voters[i].sno == sno) {
	            printf("Details of Voter with Serial Number %d:\n", sno);
	            printf("Name: %s\n", voters[i].name);
	            printf("Date of Birth: %s\n", voters[i].dob);
	            printf("Address: %s\n", voters[i].address);
	            found = 1;
	            break;
	        }
	    }
	
	    if (!found) {
	        printf("Voter not found.\n");
	    }
	}
	
	void castVote() {
	    int sno;
	    char password[50];
	    printf("Enter your voter serial number: ");
	    scanf("%d", &sno);
	    printf("Enter your password: ");
	    scanf(" %[^\n]", password);
	
	    int found = 0;
	    for (int i = 0; i < voterCount; i++) {
	        if (voters[i].sno == sno && strcmp(voters[i].password, password) == 0) {
	            printf("List of Candidates:\n");
	
	            // Read candidate list from file
	           FILE *candidateFile = fopen("candidate.txt", "r");
	if (candidateFile == NULL) {
	    perror("Error opening candidate file");
	    return;
	}
	
	
	            int candidateNumber = 1;
	            char candidateName[100], partyName[100];
	            while (fscanf(candidateFile, "%99[^,],%99[^\n]", candidateName, partyName) == 2) {
	                printf("%d. %s - %s\n", candidateNumber, candidateName, partyName);
	                candidateNumber++;
	            }
	            fclose(candidateFile);
	
	            int choice;
	            printf("Choose candidate (enter candidate number): ");
	            scanf("%d", &choice);
	
	            if (choice >= 1 && choice < candidateNumber) { // Check if the choice is within the range of available candidates
	                // Store vote information in votecount.txt
	                FILE *voteFile = fopen("votercount.txt", "a");
	                if (voteFile == NULL) {
	                    printf("Error opening file.\n");
	                    return;
	                }
	                fprintf(voteFile, "Voter Name: %s, Voter Serial Number: %d, Chosen Candidate: %s, Party: %s\n",
	                        voters[i].name, voters[i].sno, candidateName, partyName);
	                fclose(voteFile);
	
	                printf("Vote cast successfully.\n");
	            } else {
	                printf("Invalid candidate choice.\n");
	            }
	            found = 1;
	            break;
	        }
	    }
	
	    if (!found) {
	        printf("Invalid credentials.\n");
	    }
	}

