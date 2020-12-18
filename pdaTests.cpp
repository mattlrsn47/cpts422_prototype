#include <gtest/gtest.h>
#include "pdaHeader.h"

PdaObject pdaObject;

/* FUNCTIONS TO TEST */
void pdaInsert(std::ostream &output, std::istream &input);
void pdaClose(std::ostream &output);
void pdaDisplay(std::ostream &output);
//void pdaExit(std::ostream &output); exit() stops test, leave out for now
void pdaHelp(std::ostream &output);
void pdaList(std::ostream &output);
void pdaOpen(std::ostream &output, std::istream &input);
void pdaQuit(std::ostream &output);
void pdaRun(std::ostream &output, std::istream &input);
void pdaSet(std::ostream &output, std::istream &input);
void pdaShow(std::ostream &output);
void pdaView(std::ostream &output);

// Sets up generic PDA
void setupPDA()
{
  pdaObject = PdaObject();
  pdaObject.open = true;
  pdaObject.name = "Test";
  pdaObject.description = { "This", "is", "a", "test", "PDA." };
  pdaObject.stateList = { "s0", "s1", "s2" };
  pdaObject.inputAlphabetList = { 'a', 'b' };
  pdaObject.stackAlphabetList = { 'X', 'Y', 'Z' };
  pdaObject.transitionList = {  Transition("s0",'a','X',"s0","XX"),
                                Transition("s0",'a','X',"s1","X"),
                                Transition("s0",'a','Y',"s0","XY"),
                                Transition("s0",'a','Y',"s1","Y"),
                                Transition("s0",'a','Z',"s0","XZ"),
                                Transition("s0",'a','Z',"s1","Z"),
                                Transition("s0",'b','X',"s0","YX"),
                                Transition("s0",'b','X',"s1","X"),
                                Transition("s0",'b','Y',"s0","YY"),
                                Transition("s0",'b','Y',"s1","Y"),
                                Transition("s0",'b','Z',"s0","YZ"),
                                Transition("s0",'b','Z',"s1","Z"),
                                Transition("s1",'a','X',"s1","\\"),
                                Transition("s1",'b','Y',"s1","\\"),
                                Transition("s1",'\\','Z',"s2","\\")
                              };
  pdaObject.initialState = "s0";
  pdaObject.startCharacter = 'Z';
  pdaObject.finalStateList = { "s2" };
  pdaObject.inputStringList = { "aba", "ab", "\\" };
  pdaObject.stringListChanged = false;
  pdaObject.maximumTransitions = 1;
  pdaObject.maximumCharacters = 32;
  pdaObject.status = NOT_YET_RUN;
  pdaObject.accepted = false;
  pdaObject.rejected = false;
  pdaObject.originalInputString = "";
  pdaObject.branchList = {};
  pdaObject.totalTransitions = 0;
}

/* Insert1: string successfully add to list */
TEST(Insert, insert1)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup
  std::string newInputString = "abba";
  std::string expectedOutput = "String to insert into list: "+newInputString+" successfully added to list!\n\n";
  input.str(newInputString);
  std::list<std::string> expectedStringList = pdaObject.inputStringList;
  expectedStringList.push_back(newInputString);

  // test
  pdaInsert(output, input);
  EXPECT_EQ(output.str(), expectedOutput);
  EXPECT_EQ(pdaObject.inputStringList, expectedStringList);
  EXPECT_EQ(pdaObject.stringListChanged, true);
  
  // revert any changesto PDA
  setupPDA();
}

/* Insert2: pda is not open */
TEST(Insert, insert2)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup
  pdaObject.open = false;
  std::string expectedOutput = "No PDA is open to add input strings for!\n\n";

  //test
  pdaInsert(output, input);
  EXPECT_EQ(output.str(), expectedOutput);

  // revert any changes to PDA
  setupPDA();
}

/* Insert3: string has space in it */
TEST(Insert, insert3)
{

}

/* Insert4: string contatins chars not in input alphabet */
TEST(Insert, insert4)
{
  
}

/* Insert5: string already in list */
TEST(Insert, insert5)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup
  std::string expectedOutput = "String to insert into list: String is already in list!\n\n";
  input.str("aba");

  //test
  pdaInsert(output, input);
  EXPECT_EQ(output.str(), expectedOutput);
  EXPECT_EQ(pdaObject.stringListChanged, false);

  // revert any changes to PDA
  setupPDA();
}

/* Close1: no changes to input strings */
TEST(Close, close1)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Close2: changes made to input strings */
TEST(Close, close2)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Close3: pda is not open */
TEST(Close, close3)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Display1: pda has not yet run */
TEST(Display, display1)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Display2: multiple branches */
TEST(Display, display2)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Display3: pda is not open */
TEST(Display, display3)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Help */
TEST(Help, help)
{
  // input and output streams
  std::stringstream output;

  // test setup
  std::string expectedOutput ="|C|lose             Close pushdown automaton\n";
  expectedOutput+="Dis|p|lay           Display complete paths through pushdown automaton\n";
  expectedOutput+="E|x|it              Exit application\n";
  expectedOutput+="|H|elp              Help user\n";
  expectedOutput+="|I|nsert            Insert input string into list\n";
  expectedOutput+="|L|ist              List input strings\n";
  expectedOutput+="|O|pen              Open pushdown automaton\n";
  expectedOutput+="|Q|uit              Quit operation of pushdown automation on input string\n";
  expectedOutput+="|R|un               Run pushdown automaton on input string\n";
  expectedOutput+="S|e|t               Set maximum number of transitions to perform\n";
  expectedOutput+="Sho|w|              Show status of application\n";
  expectedOutput+="|V|iew              View pushdown automaton\n\n";
  //test
  pdaHelp(output);
  EXPECT_EQ(output.str(), expectedOutput);
  // revert any changes to PDA
  setupPDA();
}

/* List1: no strings in list */
TEST(List, list1)
{
  // input and output streams
  std::stringstream output;
  // test setup
  std::string expectedOutput = "\n";
  //test
  pdaObject.inputStringList = {};
  pdaList(output);
  EXPECT_EQ(output.str(), expectedOutput);
  // revert any changes to PDA
  setupPDA();
}

/* List2: multiple strings in list */
TEST(List, list2)
{
  // input and output streams
  std::stringstream output;
  // test setup
  std::string expectedOutput = "1. aba\n";
  expectedOutput+="2. ab\n";
  expectedOutput+="3. \\\n\n";
  //test
  pdaList(output);
  EXPECT_EQ(output.str(), expectedOutput);
  // revert any changes to PDA
  setupPDA();
}

/* List3: pda is not open */
TEST(List, list3)
{
  // input and output streams
  std::stringstream output;
  // test setup
  std::string expectedOutput = "No PDA is open to list input strings!\n\n";
  //test
  pdaObject.open = false;
  pdaList(output);
  EXPECT_EQ(output.str(), expectedOutput);
  // revert any changes to PDA
  setupPDA();
}

/* Open1: use "test" files */
TEST(Open, open1)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Open2: invalid file */
TEST(Open, open2)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Open3: a pda is already open */
TEST(Open, open3)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Quit1: successfully quit */
TEST(Quit, quit1)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Quit2: pda not running */
TEST(Quit, quit2)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Quit3: pda is not open */
TEST(Quit, quit3)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Run1: pda not already running, select string */
TEST(Run, run1)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Run2: pda is running, continuation */
TEST(Run, run2)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Run3: accepted string */
TEST(Run, run3)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Run4: rejected string */
TEST(Run, run4)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Run5: pda is not open */
TEST(Run, run5)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Set1: successfully set transitions */
TEST(Set, set1)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;
  // test setup
  input.str("6");
  std::string expectedOutput = "Number of transitions[";
  expectedOutput+=std::to_string(pdaObject.maximumTransitions) + "]: ";
  expectedOutput+="Set maximum transitions to " + input.str() + "\n\n";  
  //test
  pdaSet(output,input);
  EXPECT_EQ(output.str(), expectedOutput);
  // revert any changes to PDA
  setupPDA();
}

/* Set2: attempt value with a space */
TEST(Set, set2)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup
  input.str("6 7");
  std::string expectedOutput = "Number of transitions[";
  expectedOutput+=std::to_string(pdaObject.maximumTransitions) + "]: ";
  expectedOutput+="Invalid. 1 number at a time\n\n";
  //test
  pdaSet(output,input);
  EXPECT_EQ(output.str(), expectedOutput);
  // revert any changes to PDA
  setupPDA();
}

/* Set3: attempt value less than 1 */
TEST(Set, set3)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;
  // test setup
  std::string expectedOutput = "Number of transitions[" + std::to_string(pdaObject.maximumTransitions) + "]: ";
  expectedOutput+= "Invalid. Must be greater than or equal to 1\n\n";
  input.str("-1");
  //test
  pdaSet(output,input);
  EXPECT_EQ(output.str(), expectedOutput);
  // revert any changes to PDA
  setupPDA();
}

/* Set4: pda is not open */
TEST(Set, set4)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup
  std::string expectedOutput = "No PDA is open to change settings!\n\n";
  pdaObject.open = false;
  input.str("1");
  //test
  pdaSet(output,input);
  EXPECT_EQ(output.str(), expectedOutput);
  // revert any changes to PDA
  setupPDA();
}

/* Show1: pda has not yet run */
TEST(Show, show1)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Show2: pda is running */
TEST(Show, show2)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Show3: pda is not running */
TEST(Show, show3)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}

/* Show4: pda is not open */
TEST(Show, show4)
{
  // input and output streams
  std::stringstream output;

  // test setup

  //test

  // revert any changes to PDA
  setupPDA();
}
/*pdaObject.description = { "This", "is", "a", "test", "PDA." };
  pdaObject.stateList = { "s0", "s1", "s2" };
  pdaObject.inputAlphabetList = { 'a', 'b' };
  pdaObject.stackAlphabetList = { 'X', 'Y', 'Z' };
  pdaObject.transitionList = {  Transition("s0",'a','X',"s0","XX"),
                                Transition("s0",'a','X',"s1","X"),
                                Transition("s0",'a','Y',"s0","XY"),
                                Transition("s0",'a','Y',"s1","Y"),
                                Transition("s0",'a','Z',"s0","XZ"),
                                Transition("s0",'a','Z',"s1","Z"),
                                Transition("s0",'b','X',"s0","YX"),
                                Transition("s0",'b','X',"s1","X"),
                                Transition("s0",'b','Y',"s0","YY"),
                                Transition("s0",'b','Y',"s1","Y"),
                                Transition("s0",'b','Z',"s0","YZ"),
                                Transition("s0",'b','Z',"s1","Z"),
                                Transition("s1",'a','X',"s1","\\"),
                                Transition("s1",'b','Y',"s1","\\"),
                                Transition("s1",'\\','Z',"s2","\\")
                              };
  pdaObject.initialState = "s0";
  pdaObject.startCharacter = 'Z';
  pdaObject.finalStateList = { "s2" };
*/
/* View1: successfully view pda */
TEST(View, view1)
{
  // input and output streams
  std::stringstream output;
  
  // test setup
  std::string expectedOutput="This is a test PDA \n\n";
  expectedOutput+="STATES: s0 s1 s2 \n\n";
  expectedOutput+="INPUT_ALPHABET: a b \n\n";
  expectedOutput+="STACK_ALPHABET: X Y Z \n\nTRANSITION_FUNCTION:\n";
  expectedOutput+="s0 a X  s0 XX\n";
  expectedOutput+="s0 a X  s1 X\n";
  expectedOutput+="s0 a Y  s0 XY\n";
  expectedOutput+="s0 a Y  s1 Y\n";
  expectedOutput+="s0 a Z  s0 XZ\n";
  expectedOutput+="s0 a Z  s1 Z\n";
  expectedOutput+="s0 b X  s0 YX\n";
  expectedOutput+="s0 b X  s1 X\n";
  expectedOutput+="s0 b Y  s0 YY\n";
  expectedOutput+="s0 b Y  s1 Y\n";
  expectedOutput+="s0 b Z  s0 YZ\n";
  expectedOutput+="s0 b Z  s1 Z\n";
  expectedOutput+="s1 a X  s1 \\\n";
  expectedOutput+="s1 b Y  s1 \\\n";
  expectedOutput+="s1 \\ Z  s2 \\\n\n\n";
  expectedOutput+="INITIAL_STATE: s0\n\n";
  expectedOutput+="START_CHARACTER: Z\n\n";
  expectedOutput+="FINAL_STATES: s2 \n\n";
  
  //test
  pdaView(output);
  EXPECT_EQ(output.str(), expectedOutput);
  // revert any changes to PDA
  setupPDA();
}

/* View2: pda is not open */
TEST(View, view2)
{
  // input and output streams
  std::stringstream output;
  // test setup
  std::string expectedOutput ="No PDA is open to view!\n\n";
  pdaObject.open = false;
  //test
  pdaView(output);
  EXPECT_EQ(output.str(), expectedOutput);
  // revert any changes to PDA
  setupPDA();
}

int main(int argc, char **argv) {
  setupPDA(); // initialize test object
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
