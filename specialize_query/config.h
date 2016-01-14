#define LIST1WIDTH 300
#define LIST2WIDTH 578
#define BUFFERSIZE 65535
#define SQLITEDBNAME _T("ex.db")
#define SUBKEYWORD 256
#define ORGANIZATIONCATEGORY 10
#define ORGANIZATIONCATEGORYARRAY {_T("CCSA"),_T("ETSI"),_T("IEEE"),_T("IETF"),_T("ITU-T"),_T("MEF"),_T("MSA"),_T("ONF"),_T("other"),_T("privatedoc")}

struct specializelist_recoder
{
//	int id;
	CString name;
	CString category;
	CString keyword;
	CString comment;
	CString date;
};