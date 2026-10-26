#include "GuillarteDFunc.h"
#include <assert.h>

int main()
{
    printf("Starting automated verification of quiz game logic...\n");

    /* 1. Test score loading */
    struct score arrScores[MAX_SCORES];
    int scoreCount = loadScores(arrScores);
    printf("Scores loaded: %d\n", scoreCount);
    assert(scoreCount >= 1);
    assert(strcmp(arrScores[0].sName, "Dana") == 0);
    assert(arrScores[0].nScore == 1);
    printf("✓ loadScores verified successfully.\n");

    /* 2. Test reading question data from data/GuillarteDImport.txt */
    struct question arrRecords[MAX_RECORDS];
    char fileName[MAX_FILE_LEN] = "GuillarteDImport";
    int imported = readData(fileName, arrRecords, MAX_RECORDS, 0);
    printf("Records imported from %s: %d\n", fileName, imported);
    assert(imported > 0);
    assert(strcmp(arrRecords[0].sTopic, "Science") == 0);
    assert(arrRecords[0].nQNum == 1);
    assert(arrRecords[0].nCorrAns == 1); // "Cell" is choice 1
    printf("✓ readData verified successfully.\n");

    /* 3. Test findRecord */
    int found = findRecord(arrRecords, imported, "What is the smallest unit of life?", "Cell");
    assert(found == 0);
    int notFound = findRecord(arrRecords, imported, "Non-existent question", "None");
    assert(notFound == -1);
    printf("✓ findRecord verified successfully.\n");

    /* 4. Test getLastQNum */
    int lastQ = getLastQNum(arrRecords, imported, "Art");
    assert(lastQ >= 1);
    printf("✓ getLastQNum verified successfully (Last Art Q: %d).\n", lastQ);

    /* 5. Test validateAnswer */
    int ansValid = validateAnswer(arrRecords[0], "Cell");
    assert(ansValid == 0);
    int ansInvalid = validateAnswer(arrRecords[0], "NonExistentAnswer");
    assert(ansInvalid == -1);
    printf("✓ validateAnswer verified successfully.\n");

    /* 6. Test topic extraction */
    str50 sTopics[MAX_TOPICS];
    int nTopicCount = 0;
    int arrTopicIndices[MAX_RECORDS];
    displayTopics(arrRecords, imported, sTopics, &nTopicCount, arrTopicIndices);
    assert(nTopicCount >= 3);
    printf("✓ displayTopics verified successfully (%d topics detected).\n", nTopicCount);

    /* 7. Test exporting and re-reading data */
    char exportFile[MAX_FILE_LEN] = "test_export";
    writeData(exportFile, arrRecords, imported);

    struct question arrReimported[MAX_RECORDS];
    char testImportName[MAX_FILE_LEN] = "test_export";
    int reimported = readData(testImportName, arrReimported, MAX_RECORDS, 0);
    assert(reimported == imported);
    printf("✓ writeData and re-import verified successfully.\n");

    printf("\nALL AUTOMATED VERIFICATION TESTS PASSED!\n");
    return 0;
}
