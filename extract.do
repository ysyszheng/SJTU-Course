cd "/home/vincent/Documents/Obsidian Vault/Econometrics/data/"

// ***************
//    核心变量	//
// ***************
// 2010年家庭样本编码 | 18年省国标码 | 现住房价值（万元）| 现住房面积（平方米）| 全部家庭纯收入（元）| 家庭总支出（元）| 家庭净资产（元）| 2018年家庭成员人口数 | 您家现住房归谁所有
// fid provcd hp size inc comp asset num belong

// ***************
// 	2018	//
// ***************
use "./CFPS/cfps2018famecon_202101.dta", clear

// median housing prices
gen tmp = resivalue
replace tmp = . if tmp<=0
bys provcd: egen hpm = median(tmp)
/* bys provcd: egen hpm = median(resivalue) */

drop if fid18!=fid10

// 2010年家庭样本编码 | 18年省国标码 | 现住房价值（万元）| 现住房面积（平方米）| 全部家庭纯收入（元）| 家庭总支出（元）| 家庭净资产（元）| 2018年家庭成员人口数 | 您家现住房归谁所有
keep fid10 provcd18 resivalue fq801 fincome1 fincome2 pce total_asset fml_count fq2 hpm savings mortage nonhousing_debts fp407 urban18

// owner=1, renter=0, other=2 (drop)
gen belong=2
// 家庭成员拥有完全产权 | 家庭成员拥有部分产权
replace belong=1 if fq2==1|fq2==2
// 廉租房 | 公租房 | 市场上租的商品房 
replace belong=0 if fq2==4|fq2==5|fq2==6
// 公房（单位提供的房子）
drop if belong==2
drop fq2

// rename
rename (fid10 provcd18 resivalue fq801 fincome1 fincome2 pce total_asset fml_count savings mortage nonhousing_debts fp407 urban18)(fid provcd hp size inc incc comp asset num save mort debt rent urban)
gen year=2018

rm "./2018.dta"
save "./2018.dta"

// ***************
// 	2016	//
// ***************
use "./CFPS/cfps2016famecon_201807.dta", clear

// median housing prices
gen tmp = resivalue
replace tmp = . if tmp<=0
bys provcd: egen hpm = median(tmp)
/* bys provcd: egen hpm = median(resivalue) */

drop if fid16!=fid10

// 2010年家庭样本编码 | 省国标码 | 现住房价值（万元）| 现住房面积（平方米）| 全部家庭纯收入（元）| 家庭总支出 （元）| 家庭净资产（元）| 2016年家庭成员人口数 | 您家现住房归谁所有
keep fid10 provcd16 resivalue fq801 fincome1 fincome2 pce total_asset fml2016_count fq2 hpm savings mortage nonhousing_debts fp407 urban16

// owner=1, renter=0, other=2 (drop)
gen belong=2
// 家庭成员拥有完全产权 | 家庭成员拥有部分产权
replace belong=1 if fq2==1|fq2==2
// 廉租房 | 公租房 | 市场上租的商品房 
replace belong=0 if fq2==4|fq2==5|fq2==6
// 公房（单位提供的房子） | 其他
drop if belong==2
drop fq2

rename (fid10 provcd16 resivalue fq801 fincome1 fincome2 pce total_asset fml2016_count savings mortage nonhousing_debts fp407 urban16)(fid provcd hp size inc incc comp asset num save mort debt rent urban)
gen year=2016

rm "./2016.dta"
save "./2016.dta"

// ***************
// 	2014	//
// ***************
use "./CFPS/cfps2014famecon_201906.dta", clear

// median housing prices
gen tmp = resivalue
replace tmp = . if tmp<=0
bys provcd: egen hpm = median(tmp)
/* bys provcd: egen hpm = median(resivalue) */

drop if fid14!=fid10

// 2010年家庭编码 | 省国标码 | 现住房价值（万元）| 现住房面积(平方米)| 全部家庭纯收入（元）| 家庭总支出 （元）| 家庭净资产（元）| FML2014家庭成员人数 | 您家现住房归谁所有
keep fid10 provcd14 resivalue fq801 fincome1 fincome2 pce total_asset fml2014num fq2 hpm savings mortage nonhousing_debts fp407 urban14

// owner=1, renter=0, other=2 (drop)
gen belong=2
// 家庭成员拥有完全产权 | 家庭成员拥有部分产权
replace belong=1 if fq2==1|fq2==2
// 廉租房 | 公租房 | 市场上租的商品房 
replace belong=0 if fq2==4|fq2==5|fq2==6
// 公房（单位提供的房子） | 其他
drop if belong==2
drop fq2

rename (fid10 provcd14 resivalue fq801 fincome1 fincome2 pce total_asset fml2014num savings mortage nonhousing_debts fp407 urban14)(fid provcd hp size inc incc comp asset num save mort debt rent urban)
gen year=2014
rm "./2014.dta"
save "./2014.dta"

// ***************
// 	2012	//
// ***************
use "./CFPS/cfps2012famecon_201906.dta", clear

gen resivalue=resivalue_new/10000 // 单位转化为万元

// median housing prices
gen tmp = resivalue
replace tmp = . if tmp<=0
bys provcd: egen hpm = median(tmp)
/* bys provcd: egen hpm = median(resivalue) */

drop if fid12!=fid10

// 2010年家户号 | 省国标码 | 现住房价值（万元）| 现住房面积(平方米)| 全部家庭纯收入（元）| 家庭总支出 （元）| 家庭净资产（元）| 家庭人口数 | 您家现住房归谁所有
keep fid10 provcd resivalue fq701 fincome1 fincome2 pce total_asset familysize fq1 hpm savings mortage nonhousing_debts fq102m urban12

// owner=1, renter=0, other=2 (drop)
gen belong=2
// 家庭成员拥有完全产权 | 家庭成员拥有部分产权
replace belong=1 if fq1==1|fq1==2
// 廉租房 | 公租房 | 市场上租的商品房 
replace belong=0 if fq1==4|fq1==5|fq1==6
// 公房（单位提供的房子） | 其他
drop if belong==2
drop fq1

rename (fid10 provcd resivalue fq701 fincome1 fincome2 pce total_asset familysize savings mortage nonhousing_debts fq102m urban12)(fid provcd hp size inc incc comp asset num save mort debt rent urban)
gen year=2012
rm "./2012.dta"
save "./2012.dta"

// ***************
// 	2010	//
// ***************
use "./CFPS/cfps2010famecon_202008.dta", clear

gen resivalue=resivalue_new/10000

// median housing prices
gen tmp = resivalue
replace tmp = . if tmp<=0
bys provcd: egen hpm = median(tmp)
/* bys provcd: egen hpm = median(resivalue) */

// 2010年家户号 | 省国标码 | 现住房价值（万元）| 现住房面积(平方米)| 全部家庭纯收入（元）| 家庭总支出 （元）| 家庭净资产（元）| 家庭人口数 | 您家现住房归谁所有
keep fid provcd resivalue fd2 faminc_net pce total_asset familysize fd1 hpm savings mortage nonhousing_debts fh309 urban

// owner=1, renter=0, other=2 (drop)
gen belong=2
// 完全自有 | 和单位共有产权
replace belong=1 if fd1==1|fd1==2
// 租住
replace belong=0 if fd1==3
// 公房（单位提供的房子） | 其他
drop if belong==2
drop fd1

rename (fid provcd resivalue fd2 faminc_net pce total_asset familysize savings mortage nonhousing_debts fh309)(fid provcd hp size inc comp asset num save mort debt rent)
gen year=2010
rm "./2010.dta"
save "./2010.dta"
