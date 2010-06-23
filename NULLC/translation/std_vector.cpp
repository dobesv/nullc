#include "runtime.h"
// Typeid redirect table
static unsigned __nullcTR[94];
// Function pointer redirect table
static void* __nullcFR[75];
// Array classes
struct member_iterator 
{
	unsigned int classID;
	int pos;
};
struct member_info 
{
	unsigned int type;
	NULLCArray<char > name;
};
struct argument_iterator 
{
	unsigned int funcID;
	int pos;
};
struct vector 
{
	unsigned int elemType;
	int flags;
	int elemSize;
	NULLCAutoArray data;
	int currSize;
};
struct vector_iterator 
{
	vector * arr;
	int pos;
};
extern int isFunction(unsigned int type, void* unused);
extern int isClass(unsigned int type, void* unused);
extern int isSimple(unsigned int type, void* unused);
extern int isArray(unsigned int type, void* unused);
extern int isPointer(unsigned int type, void* unused);
extern int isFunction(NULLCRef type, void* unused);
extern int isClass(NULLCRef type, void* unused);
extern int isSimple(NULLCRef type, void* unused);
extern int isArray(NULLCRef type, void* unused);
extern int isPointer(NULLCRef type, void* unused);
extern int typeid__size__int_ref__(unsigned int * __context);
extern NULLCArray<char > typeid__name__char___ref__(unsigned int * __context);
extern int typeid__memberCount_int_ref__(unsigned int * __context);
extern unsigned int typeid__memberType_typeid_ref_int_(int member, unsigned int * __context);
extern NULLCArray<char > typeid__memberName_char___ref_int_(int member, unsigned int * __context);
extern unsigned int typeid__subType_typeid_ref__(unsigned int * __context);
extern int typeid__arraySize_int_ref__(unsigned int * __context);
extern unsigned int typeid__returnType_typeid_ref__(unsigned int * __context);
extern int typeid__argumentCount_int_ref__(unsigned int * __context);
extern unsigned int typeid__argumentType_typeid_ref_int_(int argument, unsigned int * __context);
extern member_iterator typeid__members_member_iterator_ref__(unsigned int * __context);
extern member_iterator * member_iterator__start_member_iterator_ref_ref__(member_iterator * __context);
extern int member_iterator__hasnext_int_ref__(member_iterator * __context);
extern member_info member_iterator__next_member_info_ref__(member_iterator * __context);
extern argument_iterator typeid__arguments_argument_iterator_ref__(unsigned int * __context);
extern argument_iterator * argument_iterator__start_argument_iterator_ref_ref__(argument_iterator * __context);
extern int argument_iterator__hasnext_int_ref__(argument_iterator * __context);
extern unsigned int argument_iterator__next_typeid_ref__(argument_iterator * __context);
void cConstructVector(vector * v, unsigned int type, int reserved, void* unused);
vector vector__(unsigned int type, int reserved, void* unused);
vector vector__(unsigned int type, void* unused);
vector_iterator vector__start_vector_iterator_ref__(vector * __context);
NULLCRef vector_iterator__next_auto_ref_ref__(vector_iterator * __context);
int vector_iterator__hasnext_int_ref__(vector_iterator * __context);
void vector__push_back_void_ref_auto_ref_(NULLCRef val, vector * __context);
void vector__pop_back_void_ref__(vector * __context);
NULLCRef vector__front_auto_ref_ref__(vector * __context);
NULLCRef vector__back_auto_ref_ref__(vector * __context);
NULLCRef __operatorIndex(vector * v, int index, void* unused);
void vector__reserve_void_ref_int_(int size, vector * __context);
void vector__resize_void_ref_int_(int size, vector * __context);
void vector__clear_void_ref__(vector * __context);
void vector__destroy_void_ref__(vector * __context);
int vector__size_int_ref__(vector * __context);
int vector__capacity_int_ref__(vector * __context);
vector  vector__(unsigned int type_0, int reserved_4, void* unused)
{
	vector ret_12;
	cConstructVector(&ret_12, *(&type_0), *(&reserved_4), (void*)0);
	return *(&ret_12);
}
vector  vector__(unsigned int type_0, void* unused)
{
	vector ret_8;
	cConstructVector(&ret_8, *(&type_0), 0, (void*)0);
	return *(&ret_8);
}
vector_iterator  vector__start_vector_iterator_ref__(vector * __context)
{
	vector_iterator iter_4;
	*(&(&iter_4)->arr) = *(&__context);
	*(&(&iter_4)->pos) = 0;
	return *(&iter_4);
}
int initStdVector()
{
	__nullcTR[0] = __nullcRegisterType(2090838615u, "void", 0, __nullcTR[0], 0, NULLC_CLASS);
	__nullcTR[1] = __nullcRegisterType(4181547808u, "double", 8, __nullcTR[0], 0, NULLC_CLASS);
	__nullcTR[2] = __nullcRegisterType(259121563u, "float", 4, __nullcTR[0], 0, NULLC_CLASS);
	__nullcTR[3] = __nullcRegisterType(2090479413u, "long", 8, __nullcTR[0], 0, NULLC_CLASS);
	__nullcTR[4] = __nullcRegisterType(193495088u, "int", 4, __nullcTR[0], 0, NULLC_CLASS);
	__nullcTR[5] = __nullcRegisterType(274395349u, "short", 2, __nullcTR[0], 0, NULLC_CLASS);
	__nullcTR[6] = __nullcRegisterType(2090147939u, "char", 1, __nullcTR[0], 0, NULLC_CLASS);
	__nullcTR[7] = __nullcRegisterType(1166360283u, "auto ref", 8, __nullcTR[0], 2, NULLC_CLASS);
	__nullcTR[8] = __nullcRegisterType(524429492u, "typeid", 4, __nullcTR[0], 1, NULLC_CLASS);
	__nullcTR[9] = __nullcRegisterType(3198057556u, "void ref", 4, __nullcTR[0], 1, NULLC_POINTER);
	__nullcTR[10] = __nullcRegisterType(4071234806u, "auto[]", 12, __nullcTR[0], 3, NULLC_CLASS);
	__nullcTR[11] = __nullcRegisterType(3150998963u, "auto ref[]", 8, __nullcTR[7], -1, NULLC_ARRAY);
	__nullcTR[12] = __nullcRegisterType(2550963152u, "void ref(int)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[13] = __nullcRegisterType(4133409083u, "char[]", 8, __nullcTR[6], -1, NULLC_ARRAY);
	__nullcTR[14] = __nullcRegisterType(3878423506u, "void ref(int,char[])", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[15] = __nullcRegisterType(1362586038u, "int ref(char[],char[])", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[16] = __nullcRegisterType(3953727713u, "char[] ref(char[],char[])", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[17] = __nullcRegisterType(3214832952u, "char[] ref", 4, __nullcTR[13], 1, NULLC_POINTER);
	__nullcTR[18] = __nullcRegisterType(90259294u, "char[] ref(char[] ref,char[])", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[19] = __nullcRegisterType(3410585167u, "char ref(char)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[20] = __nullcRegisterType(1890834067u, "short ref(short)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[21] = __nullcRegisterType(2745832905u, "int ref(int)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[22] = __nullcRegisterType(3458960563u, "long ref(long)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[23] = __nullcRegisterType(4223928607u, "float ref(float)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[24] = __nullcRegisterType(4226161577u, "double ref(double)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[25] = __nullcRegisterType(554739849u, "char[] ref()", 8, __nullcTR[0], 0, NULLC_FUNCTION);
	__nullcTR[26] = __nullcRegisterType(2528639597u, "void ref ref(int)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[27] = __nullcRegisterType(262756424u, "int[]", 8, __nullcTR[4], -1, NULLC_ARRAY);
	__nullcTR[28] = __nullcRegisterType(1780011448u, "int[] ref(int,int)", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[29] = __nullcRegisterType(3724107199u, "auto ref ref(auto ref)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[30] = __nullcRegisterType(3761170085u, "void ref()", 8, __nullcTR[0], 0, NULLC_FUNCTION);
	__nullcTR[31] = __nullcRegisterType(4190091973u, "int[] ref", 4, __nullcTR[27], 1, NULLC_POINTER);
	__nullcTR[32] = __nullcRegisterType(844911189u, "void ref() ref(auto ref,int[] ref)", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[33] = __nullcRegisterType(2671810221u, "int ref", 4, __nullcTR[4], 1, NULLC_POINTER);
	__nullcTR[34] = __nullcRegisterType(2816069557u, "char[] ref ref", 4, __nullcTR[17], 1, NULLC_POINTER);
	__nullcTR[35] = __nullcRegisterType(154671200u, "char ref", 4, __nullcTR[6], 1, NULLC_POINTER);
	__nullcTR[36] = __nullcRegisterType(2985493640u, "char[] ref ref(char[] ref,int[])", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[37] = __nullcRegisterType(2463794733u, "short[]", 8, __nullcTR[5], -1, NULLC_ARRAY);
	__nullcTR[38] = __nullcRegisterType(3958330154u, "short[] ref", 4, __nullcTR[37], 1, NULLC_POINTER);
	__nullcTR[39] = __nullcRegisterType(745297575u, "short[] ref ref", 4, __nullcTR[38], 1, NULLC_POINTER);
	__nullcTR[40] = __nullcRegisterType(3010777554u, "short ref", 4, __nullcTR[5], 1, NULLC_POINTER);
	__nullcTR[41] = __nullcRegisterType(1935747820u, "short[] ref ref(short[] ref,int[])", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[42] = __nullcRegisterType(3010510963u, "float[]", 8, __nullcTR[2], -1, NULLC_ARRAY);
	__nullcTR[43] = __nullcRegisterType(2248491120u, "float[] ref", 4, __nullcTR[42], 1, NULLC_POINTER);
	__nullcTR[44] = __nullcRegisterType(1040232248u, "double[]", 8, __nullcTR[1], -1, NULLC_ARRAY);
	__nullcTR[45] = __nullcRegisterType(2393077485u, "float[] ref ref", 4, __nullcTR[43], 1, NULLC_POINTER);
	__nullcTR[46] = __nullcRegisterType(2697529781u, "double[] ref", 4, __nullcTR[44], 1, NULLC_POINTER);
	__nullcTR[47] = __nullcRegisterType(1384297880u, "float ref", 4, __nullcTR[2], 1, NULLC_POINTER);
	__nullcTR[48] = __nullcRegisterType(3234425245u, "double ref", 4, __nullcTR[1], 1, NULLC_POINTER);
	__nullcTR[49] = __nullcRegisterType(2467461000u, "float[] ref ref(float[] ref,double[])", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[50] = __nullcRegisterType(2066091864u, "typeid ref(auto ref)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[51] = __nullcRegisterType(1268871368u, "int ref(typeid,typeid)", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[52] = __nullcRegisterType(2688408224u, "int ref(void ref(int),void ref(int))", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[53] = __nullcRegisterType(1908472638u, "int ref()", 8, __nullcTR[0], 0, NULLC_FUNCTION);
	__nullcTR[54] = __nullcRegisterType(1137649267u, "auto[] ref", 4, __nullcTR[10], 1, NULLC_POINTER);
	__nullcTR[55] = __nullcRegisterType(451037873u, "auto[] ref ref(auto[] ref,auto ref)", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[56] = __nullcRegisterType(3824954777u, "auto ref ref(auto ref,auto[] ref)", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[57] = __nullcRegisterType(3832966281u, "auto[] ref ref(auto[] ref,auto[] ref)", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[58] = __nullcRegisterType(477490926u, "auto ref ref(auto[] ref,int)", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[59] = __nullcRegisterType(1872746701u, "int ref(typeid)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[60] = __nullcRegisterType(3335638996u, "int ref(auto ref)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[61] = __nullcRegisterType(4231238349u, "typeid ref(int)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[62] = __nullcRegisterType(2745156404u, "char[] ref(int)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[63] = __nullcRegisterType(2501899970u, "typeid ref()", 8, __nullcTR[0], 0, NULLC_FUNCTION);
	__nullcTR[64] = __nullcRegisterType(1748991366u, "member_iterator", 8, __nullcTR[0], 2, NULLC_CLASS);
	__nullcTR[65] = __nullcRegisterType(3319164712u, "member_info", 12, __nullcTR[0], 2, NULLC_CLASS);
	__nullcTR[66] = __nullcRegisterType(3504529713u, "typeid ref", 4, __nullcTR[8], 1, NULLC_POINTER);
	__nullcTR[67] = __nullcRegisterType(1329745667u, "member_iterator ref", 4, __nullcTR[64], 1, NULLC_POINTER);
	__nullcTR[68] = __nullcRegisterType(1559597102u, "typeid ref ref", 4, __nullcTR[66], 1, NULLC_POINTER);
	__nullcTR[69] = __nullcRegisterType(689053972u, "member_iterator ref()", 8, __nullcTR[0], 0, NULLC_FUNCTION);
	__nullcTR[70] = __nullcRegisterType(3055261440u, "member_iterator ref ref", 4, __nullcTR[67], 1, NULLC_POINTER);
	__nullcTR[71] = __nullcRegisterType(2875022417u, "member_iterator ref ref()", 8, __nullcTR[0], 0, NULLC_FUNCTION);
	__nullcTR[72] = __nullcRegisterType(4163016061u, "member_iterator ref ref ref", 4, __nullcTR[70], 1, NULLC_POINTER);
	__nullcTR[73] = __nullcRegisterType(4051874520u, "auto ref ref", 4, __nullcTR[7], 1, NULLC_POINTER);
	__nullcTR[74] = __nullcRegisterType(2623357349u, "member_info ref", 4, __nullcTR[65], 1, NULLC_POINTER);
	__nullcTR[75] = __nullcRegisterType(682902582u, "member_info ref()", 8, __nullcTR[0], 0, NULLC_FUNCTION);
	__nullcTR[76] = __nullcRegisterType(2249706641u, "argument_iterator", 8, __nullcTR[0], 2, NULLC_CLASS);
	__nullcTR[77] = __nullcRegisterType(795945870u, "argument_iterator ref", 4, __nullcTR[76], 1, NULLC_POINTER);
	__nullcTR[78] = __nullcRegisterType(3496627295u, "argument_iterator ref()", 8, __nullcTR[0], 0, NULLC_FUNCTION);
	__nullcTR[79] = __nullcRegisterType(2485895435u, "argument_iterator ref ref", 4, __nullcTR[77], 1, NULLC_POINTER);
	__nullcTR[80] = __nullcRegisterType(1310733596u, "argument_iterator ref ref()", 8, __nullcTR[0], 0, NULLC_FUNCTION);
	__nullcTR[81] = __nullcRegisterType(1459539208u, "argument_iterator ref ref ref", 4, __nullcTR[79], 1, NULLC_POINTER);
	__nullcTR[82] = __nullcRegisterType(578531224u, "vector", 28, __nullcTR[0], 5, NULLC_CLASS);
	__nullcTR[83] = __nullcRegisterType(1368209941u, "vector ref", 4, __nullcTR[82], 1, NULLC_POINTER);
	__nullcTR[84] = __nullcRegisterType(3571091911u, "void ref(vector ref,typeid,int)", 8, __nullcTR[0], 3, NULLC_FUNCTION);
	__nullcTR[85] = __nullcRegisterType(3232773900u, "vector ref(typeid,int)", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcTR[86] = __nullcRegisterType(1013802037u, "vector ref(typeid)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[87] = __nullcRegisterType(2999426977u, "vector_iterator", 8, __nullcTR[0], 2, NULLC_CLASS);
	__nullcTR[88] = __nullcRegisterType(116655774u, "vector_iterator ref", 4, __nullcTR[87], 1, NULLC_POINTER);
	__nullcTR[89] = __nullcRegisterType(1797896978u, "vector ref ref", 4, __nullcTR[83], 1, NULLC_POINTER);
	__nullcTR[90] = __nullcRegisterType(2484087663u, "vector_iterator ref()", 8, __nullcTR[0], 0, NULLC_FUNCTION);
	__nullcTR[91] = __nullcRegisterType(1559940649u, "auto ref ref()", 8, __nullcTR[0], 0, NULLC_FUNCTION);
	__nullcTR[92] = __nullcRegisterType(1812738619u, "void ref(auto ref)", 8, __nullcTR[0], 1, NULLC_FUNCTION);
	__nullcTR[93] = __nullcRegisterType(1021024208u, "auto ref ref(vector ref,int)", 8, __nullcTR[0], 2, NULLC_FUNCTION);
	__nullcFR[0] = (void*)0;
	__nullcFR[1] = (void*)0;
	__nullcFR[2] = (void*)0;
	__nullcFR[3] = (void*)0;
	__nullcFR[4] = (void*)__operatorAdd;
	__nullcFR[5] = (void*)__operatorAddSet;
	__nullcFR[6] = (void*)char__;
	__nullcFR[7] = (void*)short__;
	__nullcFR[8] = (void*)int__;
	__nullcFR[9] = (void*)long__;
	__nullcFR[10] = (void*)float__;
	__nullcFR[11] = (void*)double__;
	__nullcFR[12] = (void*)int__str_char___ref__;
	__nullcFR[13] = (void*)__newS;
	__nullcFR[14] = (void*)__newA;
	__nullcFR[15] = (void*)duplicate;
	__nullcFR[16] = (void*)__redirect;
	__nullcFR[17] = (void*)0;
	__nullcFR[18] = (void*)0;
	__nullcFR[19] = (void*)0;
	__nullcFR[20] = (void*)typeid__;
	__nullcFR[21] = (void*)0;
	__nullcFR[22] = (void*)0;
	__nullcFR[23] = (void*)__pcomp;
	__nullcFR[24] = (void*)__pncomp;
	__nullcFR[25] = (void*)__typeCount;
	__nullcFR[26] = (void*)0;
	__nullcFR[27] = (void*)0;
	__nullcFR[28] = (void*)0;
	__nullcFR[29] = (void*)0;
	__nullcFR[30] = (void*)0;
	__nullcFR[31] = (void*)0;
	__nullcFR[32] = (void*)0;
	__nullcFR[33] = (void*)0;
	__nullcFR[34] = (void*)0;
	__nullcFR[35] = (void*)0;
	__nullcFR[36] = (void*)0;
	__nullcFR[37] = (void*)0;
	__nullcFR[38] = (void*)0;
	__nullcFR[39] = (void*)0;
	__nullcFR[40] = (void*)typeid__size__int_ref__;
	__nullcFR[41] = (void*)typeid__name__char___ref__;
	__nullcFR[42] = (void*)typeid__memberCount_int_ref__;
	__nullcFR[43] = (void*)typeid__memberType_typeid_ref_int_;
	__nullcFR[44] = (void*)typeid__memberName_char___ref_int_;
	__nullcFR[45] = (void*)typeid__subType_typeid_ref__;
	__nullcFR[46] = (void*)typeid__arraySize_int_ref__;
	__nullcFR[47] = (void*)typeid__returnType_typeid_ref__;
	__nullcFR[48] = (void*)typeid__argumentCount_int_ref__;
	__nullcFR[49] = (void*)typeid__argumentType_typeid_ref_int_;
	__nullcFR[50] = (void*)typeid__members_member_iterator_ref__;
	__nullcFR[51] = (void*)member_iterator__start_member_iterator_ref_ref__;
	__nullcFR[52] = (void*)member_iterator__hasnext_int_ref__;
	__nullcFR[53] = (void*)member_iterator__next_member_info_ref__;
	__nullcFR[54] = (void*)typeid__arguments_argument_iterator_ref__;
	__nullcFR[55] = (void*)argument_iterator__start_argument_iterator_ref_ref__;
	__nullcFR[56] = (void*)argument_iterator__hasnext_int_ref__;
	__nullcFR[57] = (void*)argument_iterator__next_typeid_ref__;
	__nullcFR[58] = (void*)cConstructVector;
	__nullcFR[59] = (void*)0;
	__nullcFR[60] = (void*)0;
	__nullcFR[61] = (void*)vector__start_vector_iterator_ref__;
	__nullcFR[62] = (void*)vector_iterator__next_auto_ref_ref__;
	__nullcFR[63] = (void*)vector_iterator__hasnext_int_ref__;
	__nullcFR[64] = (void*)vector__push_back_void_ref_auto_ref_;
	__nullcFR[65] = (void*)vector__pop_back_void_ref__;
	__nullcFR[66] = (void*)vector__front_auto_ref_ref__;
	__nullcFR[67] = (void*)vector__back_auto_ref_ref__;
	__nullcFR[68] = (void*)0;
	__nullcFR[69] = (void*)vector__reserve_void_ref_int_;
	__nullcFR[70] = (void*)vector__resize_void_ref_int_;
	__nullcFR[71] = (void*)vector__clear_void_ref__;
	__nullcFR[72] = (void*)vector__destroy_void_ref__;
	__nullcFR[73] = (void*)vector__size_int_ref__;
	__nullcFR[74] = (void*)vector__capacity_int_ref__;
	/* node translation unknown */
}
