#pragma once
#include "stdafx.h"
#include "InstructionSet.h"

class TypeInfo;
class VariableInfo;
class FunctionInfo;
struct AliasInfo;
class FunctionType;
class NodeZeroOP;
class NamespaceInfo;
struct Lexeme;

void CheckCollisionWithFunction(const char* pos, InplaceStr varName, unsigned hash, unsigned scope);

void			PushNamespace(InplaceStr space);
void			PopNamespace();
NamespaceInfo*	IsNamespace(InplaceStr space);
NamespaceInfo*	GetCurrentNamespace();
void			SetCurrentNamespace(NamespaceInfo* space);

void			PushExplicitTypes(AliasInfo* list);
AliasInfo*		GetExplicitTypes();
void			PopExplicitTypes();

TypeInfo*		SelectTypeByName(InplaceStr name);

void CallbackInitialize();

char* GetClassFunctionName(TypeInfo* type, InplaceStr funcName);

const char*	SetCurrentFunction(const char* name);
unsigned	SetCurrentArgument(unsigned argument);
TypeInfo*	GetCurrentArgumentType(const char* pos, unsigned arguments);
void		InlineFunctionImplicitReturn(const char* pos);

void AddFunctionToSortedList(FunctionInfo* info);

void SetCurrentAlignment(unsigned int alignment);

void ResetConstantFoldError();
void ThrowConstantFoldError(const char *pos);

// Function is called when block {} is opened, to save the number of defined variables and functions
void BeginBlock();
// Function is called when block {} is closed, to restore previous number of defined variables and functions to hide those that lost visibility
void EndBlock(bool hideFunctions = true, bool saveLocals = true);

// Functions for adding nodes with constant numbers of different types
void AddNumberNodeChar(const char* pos);
void AddNumberNodeInt(const char* pos);
void AddNumberNodeFloat(const char* pos);
void AddNumberNodeLong(const char* pos, const char* end);
void AddNumberNodeDouble(const char* pos);

void AddVoidNode();
void AddNullPointer();

void AddHexInteger(const char* pos, const char* end);
void AddOctInteger(const char* pos, const char* end);
void AddBinInteger(const char* pos, const char* end);

void AddGeneratorReturnData(const char *pos);

// Function that places string on stack, using list of NodeNumber in NodeExpressionList
void AddStringNode(const char* s, const char* e, bool unescaped);

// Function that creates node that removes value on top of the stack
void AddPopNode(const char* pos);

// For unary operator +
void AddPositiveNode(const char* pos);

// Function that creates unary operation node that changes sign of value
void AddNegateNode(const char* pos);

// Function that creates unary operation node for logical NOT
void AddLogNotNode(const char* pos);
// Function that creates unary operation node for binary NOT
void AddBitNotNode(const char* pos);

void AddBinaryCommandNode(const char* pos, CmdID id);

void AddReturnNode(const char* pos, bool yield = false);
void AddBreakNode(const char* pos);
void AddContinueNode(const char* pos);

void SelectTypeByPointer(TypeInfo* type);
void SelectTypeForGeneric(Lexeme* pos, unsigned nodeIndex);
void SelectTypeByIndex(unsigned int index);
TypeInfo* GetSelectedType();
const char* GetSelectedTypeName();

FunctionInfo* GetCurrentFunction();

VariableInfo* AddVariable(const char* pos, InplaceStr varName, bool preserveNamespace = true, bool allowThis = false, bool allowCollision = false);

void AddVariableReserveNode(const char* pos);

void ConvertTypeToReference(const char* pos);

void ConvertTypeToArray(const char* pos);

void GetTypeSize(const char* pos, bool sizeOfExpr);
void GetTypeId(const char* pos);

void SetTypeOfLastNode(const char* pos);

// Function that retrieves variable address
void AddGetAddressNode(const char* pos, InplaceStr varName);

// Function for array indexing
void AddArrayIndexNode(const char* pos, unsigned argumentCount = 1);

// Function for variable assignment in place of definition
void AddDefineVariableNode(const char* pos, VariableInfo* varInfo, bool noOverload = false);

void AddSetVariableNode(const char* pos);

void AddGetVariableNode(const char* pos, bool forceError = false);
void AddMemberAccessNode(const char* pos, InplaceStr varName);

void UndoDereferceNode(const char* pos);
const static bool	OP_INCREMENT = 1;
const static bool	OP_DECREMENT = 0;
const static bool	OP_PREFIX = 1;
const static bool	OP_POSTFIX = 0;
void AddUnaryModifyOpNode(const char* pos, bool isInc, bool prefixOp);

void AddModifyVariableNode(const char* pos, CmdID cmd, const char* name);

void AddOneExpressionNode(TypeInfo* retType = NULL);
void AddTwoExpressionNode(TypeInfo* retType = NULL);

void AddArrayConstructor(const char* pos, unsigned int arrElementCount);

void AddArrayIterator(const char* pos, InplaceStr varName, TypeInfo* type, bool extra = false);
void MergeArrayIterators();

void AddTypeAllocation(const char* pos, bool arrayType = false);
void AddDefaultConstructorCall(const char* pos, const char* name);
NodeZeroOP* PrepareConstructorCall(const char* pos);
void FinishConstructorCall(const char* pos);
const char*	FindConstructorName(TypeInfo* type);
bool HasConstructor(TypeInfo* type, unsigned arguments, bool* callDefault = NULL);

void BeginCoroutine();
void FunctionAdd(const char* pos, const char* funcName, bool isOperator = false);
void FunctionParameter(const char* pos, InplaceStr paramName);
void FunctionParameterExplicit();
void FunctionPrepareDefault();
void FunctionParameterDefault(const char* pos);
void FunctionPrototype(const char* pos);
void FunctionStart(const char* pos);
void FunctionEnd(const char* pos);
void FunctionToOperator(const char* pos);
bool FunctionGeneric(bool setGeneric, unsigned pos = 0);

void SelectFunctionsForHash(unsigned funcNameHash, unsigned scope);
unsigned SelectBestFunction(unsigned count, unsigned callArgCount, unsigned int &minRating, TypeInfo* forcedParentType = NULL, bool hideGenerics = true);

unsigned GetFunctionRating(FunctionType *currFunc, unsigned callArgCount, VariableInfo *currArgument);
bool AddFunctionCallNode(const char* pos, const char* funcName, unsigned int callArgCount, bool silent = false, FunctionInfo* templateFunc = NULL, TypeInfo* forcedParentType = NULL);
bool PrepareMemberCall(const char* pos, const char* funcName = NULL);
bool AddMemberFunctionCall(const char* pos, const char* funcName, unsigned int callArgCount, bool silent = false);

void AddIfNode(const char* pos);
void AddIfElseNode(const char* pos);
void AddIfElseTermNode(const char* pos);

void IncreaseCycleDepth();

void AddForEachNode(const char* pos);
void AddForNode(const char* pos);
void AddWhileNode(const char* pos);
void AddDoWhileNode(const char* pos);

void BeginSwitch(const char* pos);
void AddCaseNode(const char* pos);
void AddDefaultNode();
void EndSwitch();

TypeInfo* TypeBegin(const char* pos, const char* end, bool addNamespace = true, unsigned aliasCount = 0);
void TypeAddMember(const char* pos, const char* varName);
void TypeAddConstant(const char* pos, const char* constName);
void TypePrototypeFinish();
void TypeFinish();
void TypeContinue(const char* pos);
void TypeStop();
void TypeGeneric(unsigned pos);
void TypeInstanceGeneric(const char* pos, TypeInfo* base, unsigned aliases, bool genericTemp = false);
void TypeDeriveFrom(const char* pos, TypeInfo* type);
TypeInfo*	GetDefinedType();
unsigned ResetDefinedTypeState();
void RestoreDefinedTypeState(TypeInfo* type, unsigned methodCount);
void TypeExtendable(const char* pos);

void AddAliasType(InplaceStr aliasName, bool addToTypeTable);

void AddUnfixedArraySize();

void RestoreRedirectionTables();
void CreateRedirectionTables();

void RestoreScopedGlobals();
void RestoreNamespaces(bool undo, NamespaceInfo *parent, unsigned& prevBackupSize, unsigned& prevStackSize, NamespaceInfo*& lastNS);

unsigned int GetGlobalSize();
void SetGlobalSize(unsigned int offset);

void CallbackReset();

FunctionInfo* InstanceGenericFunctionForType(const char* pos, FunctionInfo *info, TypeInfo *dstPreferred, unsigned count, bool create, bool silentError, NodeZeroOP **funcDefNode = NULL);
TypeInfo* InstanceGenericFunctionTypeForType(const char* pos, FunctionInfo *info, TypeInfo *dstPreferred, unsigned count, bool create, bool silentError, NodeZeroOP **funcDefNode = NULL);
