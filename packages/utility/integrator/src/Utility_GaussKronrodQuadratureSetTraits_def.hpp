//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodQuadratureSetTraits_def.hpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod quadrature set traits
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_DEF_HPP
#define UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_DEF_HPP

namespace Utility{

/******************* 15 point rule *******************/
// Gauss quadrature weights
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<15,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::gauss_weights =
  GaussKronrodQuadratureSetTraits<15,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeGaussWeights();

// Kronrod quadrature weights
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<15,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::kronrod_weights =
  GaussKronrodQuadratureSetTraits<15,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodWeights();

// Kronrod quadrature abscissae
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<15,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::kronrod_abscissae =
  GaussKronrodQuadratureSetTraits<15,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodAbscissae();

// Initialize the gauss weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<15,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeGaussWeights()
{
  std::vector<FloatType> gauss_weights(4);
  gauss_weights[0] = (FloatType)0.129484966168869693270611432679082L;
  gauss_weights[1] = (FloatType)0.279705391489276667901467771423780L;
  gauss_weights[2] = (FloatType)0.381830050505118944950369775488975L;
  gauss_weights[3] = (FloatType)0.417959183673469387755102040816327L;

  return gauss_weights;
}

// Initialize the kronrod weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<15,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodWeights()
{
  std::vector<FloatType> kronrod_weights(8);
  kronrod_weights[0] = (FloatType)0.022935322010529224963732008058970L;
  kronrod_weights[1] = (FloatType)0.063092092629978553290700663189204L;
  kronrod_weights[2] = (FloatType)0.104790010322250183839876322541518L;
  kronrod_weights[3] = (FloatType)0.140653259715525918745189590510238L;
  kronrod_weights[4] = (FloatType)0.169004726639267902826583426598550L;
  kronrod_weights[5] = (FloatType)0.190350578064785409913256402421014L;
  kronrod_weights[6] = (FloatType)0.204432940075298892414161999234649L;
  kronrod_weights[7] = (FloatType)0.209482141084727828012999174891714L;

  return kronrod_weights;
}

// Initialize the gauss weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<15,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodAbscissae()
{
  std::vector<FloatType> kronrod_abscissae(8);
  kronrod_abscissae[0] = (FloatType)0.991455371120812639206854697526329L;
  kronrod_abscissae[1] = (FloatType)0.949107912342758524526189684047851L;
  kronrod_abscissae[2] = (FloatType)0.864864423359769072789712788640926L;
  kronrod_abscissae[3] = (FloatType)0.741531185599394439863864773280788L;
  kronrod_abscissae[4] = (FloatType)0.586087235467691130294144838258730L;
  kronrod_abscissae[5] = (FloatType)0.405845151377397166906606412076961L;
  kronrod_abscissae[6] = (FloatType)0.207784955007898467600689403773245L;
  kronrod_abscissae[7] = (FloatType)0.000000000000000000000000000000000L;

  return kronrod_abscissae;
}

/******************* 21 point rule *******************/
// Gauss quadrature weights
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<21,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::gauss_weights =
  GaussKronrodQuadratureSetTraits<21,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeGaussWeights();

// Kronrod quadrature weights
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<21,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::kronrod_weights =
  GaussKronrodQuadratureSetTraits<21,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodWeights();

// Kronrod quadrature abscissae
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<21,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::kronrod_abscissae =
  GaussKronrodQuadratureSetTraits<21,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodAbscissae();

// Initialize the gauss weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<21,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeGaussWeights()
{
  std::vector<FloatType> gauss_weights(5);
  gauss_weights[0] = (FloatType)0.066671344308688137593568809893332L;
  gauss_weights[1] = (FloatType)0.149451349150580593145776339657697L;
  gauss_weights[2] = (FloatType)0.219086362515982043995534934228163L;
  gauss_weights[3] = (FloatType)0.269266719309996355091226921569469L;
  gauss_weights[4] = (FloatType)0.295524224714752870173892994651338L;

  return gauss_weights;
}

// Initialize the kronrod weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<21,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodWeights()
{
  std::vector<FloatType> kronrod_weights(11);
  kronrod_weights[0] = (FloatType)0.011694638867371874278064396062192L;
  kronrod_weights[1] = (FloatType)0.032558162307964727478818972459390L;
  kronrod_weights[2] = (FloatType)0.054755896574351996031381300244580L;
  kronrod_weights[3] = (FloatType)0.075039674810919952767043140916190L;
  kronrod_weights[4] = (FloatType)0.093125454583697605535065465083366L;
  kronrod_weights[5] = (FloatType)0.109387158802297641899210590325805L;
  kronrod_weights[6] = (FloatType)0.123491976262065851077958109831074L;
  kronrod_weights[7] = (FloatType)0.134709217311473325928054001771707L;
  kronrod_weights[8] = (FloatType)0.142775938577060080797094273138717L;
  kronrod_weights[9] = (FloatType)0.147739104901338491374841515972068L;
  kronrod_weights[10] = (FloatType)0.149445554002916905664936468389821L;

  return kronrod_weights;
}

// Initialize the gauss weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<21,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodAbscissae()
{
  std::vector<FloatType> kronrod_abscissae(11);
  kronrod_abscissae[0] = (FloatType)0.995657163025808080735527280689003L;
  kronrod_abscissae[1] = (FloatType)0.973906528517171720077964012084452L;
  kronrod_abscissae[2] = (FloatType)0.930157491355708226001207180059508L;
  kronrod_abscissae[3] = (FloatType)0.865063366688984510732096688423493L;
  kronrod_abscissae[4] = (FloatType)0.780817726586416897063717578345042L;
  kronrod_abscissae[5] = (FloatType)0.679409568299024406234327365114874L;
  kronrod_abscissae[6] = (FloatType)0.562757134668604683339000099272694L;
  kronrod_abscissae[7] = (FloatType)0.433395394129247190799265943165784L;
  kronrod_abscissae[8] = (FloatType)0.294392862701460198131126603103866L;
  kronrod_abscissae[9] = (FloatType)0.148874338981631210884826001129720L;
  kronrod_abscissae[10] = (FloatType)0.000000000000000000000000000000000L;

  return kronrod_abscissae;
}

/******************* 31 point rule *******************/
// Gauss quadrature weights
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<31,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::gauss_weights =
  GaussKronrodQuadratureSetTraits<31,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeGaussWeights();

// Kronrod quadrature weights
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<31,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::kronrod_weights =
  GaussKronrodQuadratureSetTraits<31,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodWeights();

// Kronrod quadrature abscissae
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<31,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::kronrod_abscissae =
  GaussKronrodQuadratureSetTraits<31,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodAbscissae();

// Initialize the gauss weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<31,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeGaussWeights()
{
  std::vector<FloatType> gauss_weights(8);
  gauss_weights[0] = (FloatType)0.030753241996117268354628393577204L;
  gauss_weights[1] = (FloatType)0.070366047488108124709267416450667L;
  gauss_weights[2] = (FloatType)0.107159220467171935011869546685869L;
  gauss_weights[3] = (FloatType)0.139570677926154314447804794511028L;
  gauss_weights[4] = (FloatType)0.166269205816993933553200860481209L;
  gauss_weights[5] = (FloatType)0.186161000015562211026800561866423L;
  gauss_weights[6] = (FloatType)0.198431485327111576456118326443839L;
  gauss_weights[7] = (FloatType)0.202578241925561272880620199967519L;

  return gauss_weights;
}

// Initialize the kronrod weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<31,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodWeights()
{
  std::vector<FloatType> kronrod_weights(16);
  kronrod_weights[0] = (FloatType)0.005377479872923348987792051430128L;
  kronrod_weights[1] = (FloatType)0.015007947329316122538374763075807L;
  kronrod_weights[2] = (FloatType)0.025460847326715320186874001019653L;
  kronrod_weights[3] = (FloatType)0.035346360791375846222037948478360L;
  kronrod_weights[4] = (FloatType)0.044589751324764876608227299373280L;
  kronrod_weights[5] = (FloatType)0.053481524690928087265343147239430L;
  kronrod_weights[6] = (FloatType)0.062009567800670640285139230960803L;
  kronrod_weights[7] = (FloatType)0.069854121318728258709520077099147L;
  kronrod_weights[8] = (FloatType)0.076849680757720378894432777482659L;
  kronrod_weights[9] = (FloatType)0.083080502823133021038289247286104L;
  kronrod_weights[10] = (FloatType)0.088564443056211770647275443693774L;
  kronrod_weights[11] = (FloatType)0.093126598170825321225486872747346L;
  kronrod_weights[12] = (FloatType)0.096642726983623678505179907627589L;
  kronrod_weights[13] = (FloatType)0.099173598721791959332393173484603L;
  kronrod_weights[14] = (FloatType)0.100769845523875595044946662617570L;
  kronrod_weights[15] = (FloatType)0.101330007014791549017374792767493L;

  return kronrod_weights;
}

// Initialize the gauss weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<31,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodAbscissae()
{
  std::vector<FloatType> kronrod_abscissae(16);
  kronrod_abscissae[0] = (FloatType)0.998002298693397060285172840152271L;
  kronrod_abscissae[1] = (FloatType)0.987992518020485428489565718586613L;
  kronrod_abscissae[2] = (FloatType)0.967739075679139134257347978784337L;
  kronrod_abscissae[3] = (FloatType)0.937273392400705904307758947710209L;
  kronrod_abscissae[4] = (FloatType)0.897264532344081900882509656454496L;
  kronrod_abscissae[5] = (FloatType)0.848206583410427216200648320774217L;
  kronrod_abscissae[6] = (FloatType)0.790418501442465932967649294817947L;
  kronrod_abscissae[7] = (FloatType)0.724417731360170047416186054613938L;
  kronrod_abscissae[8] = (FloatType)0.650996741297416970533735895313275L;
  kronrod_abscissae[9] = (FloatType)0.570972172608538847537226737253911L;
  kronrod_abscissae[10] = (FloatType)0.485081863640239680693655740232351L;
  kronrod_abscissae[11] = (FloatType)0.394151347077563369897207370981045L;
  kronrod_abscissae[12] = (FloatType)0.299180007153168812166780024266389L;
  kronrod_abscissae[13] = (FloatType)0.201194093997434522300628303394596L;
  kronrod_abscissae[14] = (FloatType)0.101142066918717499027074231447392L;
  kronrod_abscissae[15] = (FloatType)0.000000000000000000000000000000000L;

  return kronrod_abscissae;
}

/******************* 41 point rule *******************/
// Gauss quadrature weights
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<41,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::gauss_weights =
  GaussKronrodQuadratureSetTraits<41,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeGaussWeights();

// Kronrod quadrature weights
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<41,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::kronrod_weights =
  GaussKronrodQuadratureSetTraits<41,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodWeights();

// Kronrod quadrature abscissae
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<41,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::kronrod_abscissae =
  GaussKronrodQuadratureSetTraits<41,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodAbscissae();

// Initialize the gauss weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<41,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeGaussWeights()
{
  std::vector<FloatType> gauss_weights(10);
  gauss_weights[0] = (FloatType)0.017614007139152118311861962351853L;
  gauss_weights[1] = (FloatType)0.040601429800386941331039952274932L;
  gauss_weights[2] = (FloatType)0.062672048334109063569506535187042L;
  gauss_weights[3] = (FloatType)0.083276741576704748724758143222046L;
  gauss_weights[4] = (FloatType)0.101930119817240435036750135480350L;
  gauss_weights[5] = (FloatType)0.118194531961518417312377377711382L;
  gauss_weights[6] = (FloatType)0.131688638449176626898494499748163L;
  gauss_weights[7] = (FloatType)0.142096109318382051329298325067165L;
  gauss_weights[8] = (FloatType)0.149172986472603746787828737001969L;
  gauss_weights[9] = (FloatType)0.152753387130725850698084331955098L;

  return gauss_weights;
}

// Initialize the kronrod weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<41,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodWeights()
{
  std::vector<FloatType> kronrod_weights(21);
  kronrod_weights[0] = (FloatType)0.003073583718520531501218293246031L;
  kronrod_weights[1] = (FloatType)0.008600269855642942198661787950102L;
  kronrod_weights[2] = (FloatType)0.014626169256971252983787960308868L;
  kronrod_weights[3] = (FloatType)0.020388373461266523598010231432755L;
  kronrod_weights[4] = (FloatType)0.025882133604951158834505067096153L;
  kronrod_weights[5] = (FloatType)0.031287306777032798958543119323801L;
  kronrod_weights[6] = (FloatType)0.036600169758200798030557240707211L;
  kronrod_weights[7] = (FloatType)0.041668873327973686263788305936895L;
  kronrod_weights[8] = (FloatType)0.046434821867497674720231880926108L;
  kronrod_weights[9] = (FloatType)0.050944573923728691932707670050345L;
  kronrod_weights[10] = (FloatType)0.055195105348285994744832372419777L;
  kronrod_weights[11] = (FloatType)0.059111400880639572374967220648594L;
  kronrod_weights[12] = (FloatType)0.062653237554781168025870122174255L;
  kronrod_weights[13] = (FloatType)0.065834597133618422111563556969398L;
  kronrod_weights[14] = (FloatType)0.068648672928521619345623411885368L;
  kronrod_weights[15] = (FloatType)0.071054423553444068305790361723210L;
  kronrod_weights[16] = (FloatType)0.073030690332786667495189417658913L;
  kronrod_weights[17] = (FloatType)0.074582875400499188986581418362488L;
  kronrod_weights[18] = (FloatType)0.075704497684556674659542775376617L;
  kronrod_weights[19] = (FloatType)0.076377867672080736705502835038061L;
  kronrod_weights[20] = (FloatType)0.076600711917999656445049901530102L;

  return kronrod_weights;
}

// Initialize the gauss weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<41,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodAbscissae()
{
  std::vector<FloatType> kronrod_abscissae(21);
  kronrod_abscissae[0] = (FloatType)0.998859031588277663838315576545863L;
  kronrod_abscissae[1] = (FloatType)0.993128599185094924786122388471320L;
  kronrod_abscissae[2] = (FloatType)0.981507877450250259193342994720217L;
  kronrod_abscissae[3] = (FloatType)0.963971927277913791267666131197277L;
  kronrod_abscissae[4] = (FloatType)0.940822633831754753519982722212443L;
  kronrod_abscissae[5] = (FloatType)0.912234428251325905867752441203298L;
  kronrod_abscissae[6] = (FloatType)0.878276811252281976077442995113078L;
  kronrod_abscissae[7] = (FloatType)0.839116971822218823394529061701521L;
  kronrod_abscissae[8] = (FloatType)0.795041428837551198350638833272788L;
  kronrod_abscissae[9] = (FloatType)0.746331906460150792614305070355642L;
  kronrod_abscissae[10] = (FloatType)0.693237656334751384805490711845932L;
  kronrod_abscissae[11] = (FloatType)0.636053680726515025452836696226286L;
  kronrod_abscissae[12] = (FloatType)0.575140446819710315342946036586425L;
  kronrod_abscissae[13] = (FloatType)0.510867001950827098004364050955251L;
  kronrod_abscissae[14] = (FloatType)0.443593175238725103199992213492640L;
  kronrod_abscissae[15] = (FloatType)0.373706088715419560672548177024927L;
  kronrod_abscissae[16] = (FloatType)0.301627868114913004320555356858592L;
  kronrod_abscissae[17] = (FloatType)0.227785851141645078080496195368575L;
  kronrod_abscissae[18] = (FloatType)0.152605465240922675505220241022678L;
  kronrod_abscissae[19] = (FloatType)0.076526521133497333754640409398838L;
  kronrod_abscissae[20] = (FloatType)0.000000000000000000000000000000000L;

  return kronrod_abscissae;
}

/******************* 51 point rule *******************/
// Gauss quadrature weights
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<51,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::gauss_weights =
  GaussKronrodQuadratureSetTraits<51,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeGaussWeights();

// Kronrod quadrature weights
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<51,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::kronrod_weights =
  GaussKronrodQuadratureSetTraits<51,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodWeights();

// Kronrod quadrature abscissae
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<51,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::kronrod_abscissae =
  GaussKronrodQuadratureSetTraits<51,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodAbscissae();

// Initialize the gauss weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<51,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeGaussWeights()
{
  std::vector<FloatType> gauss_weights(13);
  gauss_weights[0] = (FloatType)0.011393798501026287947902964113235L;
  gauss_weights[1] = (FloatType)0.026354986615032137261901815295299L;
  gauss_weights[2] = (FloatType)0.040939156701306312655623487711646L;
  gauss_weights[3] = (FloatType)0.054904695975835191925936891540473L;
  gauss_weights[4] = (FloatType)0.068038333812356917207187185656708L;
  gauss_weights[5] = (FloatType)0.080140700335001018013234959669111L;
  gauss_weights[6] = (FloatType)0.091028261982963649811497220702892L;
  gauss_weights[7] = (FloatType)0.100535949067050644202206890392686L;
  gauss_weights[8] = (FloatType)0.108519624474263653116093957050117L;
  gauss_weights[9] = (FloatType)0.114858259145711648339325545869556L;
  gauss_weights[10] = (FloatType)0.119455763535784772228178126512901L;
  gauss_weights[11] = (FloatType)0.122242442990310041688959518945852L;
  gauss_weights[12] = (FloatType)0.123176053726715451203902873079050L;

  return gauss_weights;
}

// Initialize the kronrod weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<51,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodWeights()
{
  std::vector<FloatType> kronrod_weights(26);
  kronrod_weights[0] = (FloatType)0.001987383892330315926507851882843L;
  kronrod_weights[1] = (FloatType)0.005561932135356713758040236901066L;
  kronrod_weights[2] = (FloatType)0.009473973386174151607207710523655L;
  kronrod_weights[3] = (FloatType)0.013236229195571674813656405846976L;
  kronrod_weights[4] = (FloatType)0.016847817709128298231516667536336L;
  kronrod_weights[5] = (FloatType)0.020435371145882835456568292235939L;
  kronrod_weights[6] = (FloatType)0.024009945606953216220092489164881L;
  kronrod_weights[7] = (FloatType)0.027475317587851737802948455517811L;
  kronrod_weights[8] = (FloatType)0.030792300167387488891109020215229L;
  kronrod_weights[9] = (FloatType)0.034002130274329337836748795229551L;
  kronrod_weights[10] = (FloatType)0.037116271483415543560330625367620L;
  kronrod_weights[11] = (FloatType)0.040083825504032382074839284467076L;
  kronrod_weights[12] = (FloatType)0.042872845020170049476895792439495L;
  kronrod_weights[13] = (FloatType)0.045502913049921788909870584752660L;
  kronrod_weights[14] = (FloatType)0.047982537138836713906392255756915L;
  kronrod_weights[15] = (FloatType)0.050277679080715671963325259433440L;
  kronrod_weights[16] = (FloatType)0.052362885806407475864366712137873L;
  kronrod_weights[17] = (FloatType)0.054251129888545490144543370459876L;
  kronrod_weights[18] = (FloatType)0.055950811220412317308240686382747L;
  kronrod_weights[19] = (FloatType)0.057437116361567832853582693939506L;
  kronrod_weights[20] = (FloatType)0.058689680022394207961974175856788L;
  kronrod_weights[21] = (FloatType)0.059720340324174059979099291932562L;
  kronrod_weights[22] = (FloatType)0.060539455376045862945360267517565L;
  kronrod_weights[23] = (FloatType)0.061128509717053048305859030416293L;
  kronrod_weights[24] = (FloatType)0.061471189871425316661544131965264L;
  kronrod_weights[25] = (FloatType)0.061580818067832935078759824240066L;

  return kronrod_weights;
}

// Initialize the gauss weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<51,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodAbscissae()
{
  std::vector<FloatType> kronrod_abscissae(26);
  kronrod_abscissae[0] = (FloatType)0.999262104992609834193457486540341L;
  kronrod_abscissae[1] = (FloatType)0.995556969790498097908784946893902L;
  kronrod_abscissae[2] = (FloatType)0.988035794534077247637331014577406L;
  kronrod_abscissae[3] = (FloatType)0.976663921459517511498315386479594L;
  kronrod_abscissae[4] = (FloatType)0.961614986425842512418130033660167L;
  kronrod_abscissae[5] = (FloatType)0.942974571228974339414011169658471L;
  kronrod_abscissae[6] = (FloatType)0.920747115281701561746346084546331L;
  kronrod_abscissae[7] = (FloatType)0.894991997878275368851042006782805L;
  kronrod_abscissae[8] = (FloatType)0.865847065293275595448996969588340L;
  kronrod_abscissae[9] = (FloatType)0.833442628760834001421021108693570L;
  kronrod_abscissae[10] = (FloatType)0.797873797998500059410410904994307L;
  kronrod_abscissae[11] = (FloatType)0.759259263037357630577282865204361L;
  kronrod_abscissae[12] = (FloatType)0.717766406813084388186654079773298L;
  kronrod_abscissae[13] = (FloatType)0.673566368473468364485120633247622L;
  kronrod_abscissae[14] = (FloatType)0.626810099010317412788122681624518L;
  kronrod_abscissae[15] = (FloatType)0.577662930241222967723689841612654L;
  kronrod_abscissae[16] = (FloatType)0.526325284334719182599623778158010L;
  kronrod_abscissae[17] = (FloatType)0.473002731445714960522182115009192L;
  kronrod_abscissae[18] = (FloatType)0.417885382193037748851814394594572L;
  kronrod_abscissae[19] = (FloatType)0.361172305809387837735821730127641L;
  kronrod_abscissae[20] = (FloatType)0.303089538931107830167478909980339L;
  kronrod_abscissae[21] = (FloatType)0.243866883720988432045190362797452L;
  kronrod_abscissae[22] = (FloatType)0.183718939421048892015969888759528L;
  kronrod_abscissae[23] = (FloatType)0.122864692610710396387359818808037L;
  kronrod_abscissae[24] = (FloatType)0.061544483005685078886546392366797L;
  kronrod_abscissae[25] = (FloatType)0.000000000000000000000000000000000L;

  return kronrod_abscissae;
}

/******************* 61 point rule *******************/
// Gauss quadrature weights
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<61,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::gauss_weights =
  GaussKronrodQuadratureSetTraits<61,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeGaussWeights();

// Kronrod quadrature weights
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<61,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::kronrod_weights =
  GaussKronrodQuadratureSetTraits<61,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodWeights();

// Kronrod quadrature abscissae
template<typename FloatType>
const std::vector<FloatType> GaussKronrodQuadratureSetTraits<61,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::kronrod_abscissae =
  GaussKronrodQuadratureSetTraits<61,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodAbscissae();

// Initialize the gauss weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<61,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeGaussWeights()
{
  std::vector<FloatType> gauss_weights(15);
  gauss_weights[0] = (FloatType)0.007968192496166605615465883474674L;
  gauss_weights[1] = (FloatType)0.018466468311090959142302131912047L;
  gauss_weights[2] = (FloatType)0.028784707883323369349719179611292L;
  gauss_weights[3] = (FloatType)0.038799192569627049596801936446348L;
  gauss_weights[4] = (FloatType)0.048402672830594052902938140422808L;
  gauss_weights[5] = (FloatType)0.057493156217619066481721689402056L;
  gauss_weights[6] = (FloatType)0.065974229882180495128128515115962L;
  gauss_weights[7] = (FloatType)0.073755974737705206268243850022191L;
  gauss_weights[8] = (FloatType)0.080755895229420215354694938460530L;
  gauss_weights[9] = (FloatType)0.086899787201082979802387530715126L;
  gauss_weights[10] = (FloatType)0.092122522237786128717632707087619L;
  gauss_weights[11] = (FloatType)0.096368737174644259639468626351810L;
  gauss_weights[12] = (FloatType)0.099593420586795267062780282103569L;
  gauss_weights[13] = (FloatType)0.101762389748405504596428952168554L;
  gauss_weights[14] = (FloatType)0.102852652893558840341285636705415L;

  return gauss_weights;
}

// Initialize the kronrod weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<61,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodWeights()
{
  std::vector<FloatType> kronrod_weights(31);
  kronrod_weights[0] = (FloatType)0.001389013698677007624551591226760L;
  kronrod_weights[1] = (FloatType)0.003890461127099884051267201844516L;
  kronrod_weights[2] = (FloatType)0.006630703915931292173319826369750L;
  kronrod_weights[3] = (FloatType)0.009273279659517763428441146892024L;
  kronrod_weights[4] = (FloatType)0.011823015253496341742232898853251L;
  kronrod_weights[5] = (FloatType)0.014369729507045804812451432443580L;
  kronrod_weights[6] = (FloatType)0.016920889189053272627572289420322L;
  kronrod_weights[7] = (FloatType)0.019414141193942381173408951050128L;
  kronrod_weights[8] = (FloatType)0.021828035821609192297167485738339L;
  kronrod_weights[9] = (FloatType)0.024191162078080601365686370725232L;
  kronrod_weights[10] = (FloatType)0.026509954882333101610601709335075L;
  kronrod_weights[11] = (FloatType)0.028754048765041292843978785354334L;
  kronrod_weights[12] = (FloatType)0.030907257562387762472884252943092L;
  kronrod_weights[13] = (FloatType)0.032981447057483726031814191016854L;
  kronrod_weights[14] = (FloatType)0.034979338028060024137499670731468L;
  kronrod_weights[15] = (FloatType)0.036882364651821229223911065617136L;
  kronrod_weights[16] = (FloatType)0.038678945624727592950348651532281L;
  kronrod_weights[17] = (FloatType)0.040374538951535959111995279752468L;
  kronrod_weights[18] = (FloatType)0.041969810215164246147147541285970L;
  kronrod_weights[19] = (FloatType)0.043452539701356069316831728117073L;
  kronrod_weights[20] = (FloatType)0.044814800133162663192355551616723L;
  kronrod_weights[21] = (FloatType)0.046059238271006988116271735559374L;
  kronrod_weights[22] = (FloatType)0.047185546569299153945261478181099L;
  kronrod_weights[23] = (FloatType)0.048185861757087129140779492298305L;
  kronrod_weights[24] = (FloatType)0.049055434555029778887528165367238L;
  kronrod_weights[25] = (FloatType)0.049795683427074206357811569379942L;
  kronrod_weights[26] = (FloatType)0.050405921402782346840893085653585L;
  kronrod_weights[27] = (FloatType)0.050881795898749606492297473049805L;
  kronrod_weights[28] = (FloatType)0.051221547849258772170656282604944L;
  kronrod_weights[29] = (FloatType)0.051426128537459025933862879215781L;
  kronrod_weights[30] = (FloatType)0.051494729429451567558340433647099L;

  return kronrod_weights;
}

// Initialize the gauss weight array
template<typename FloatType>
std::vector<FloatType> GaussKronrodQuadratureSetTraits<61,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>::initializeKronrodAbscissae()
{
  std::vector<FloatType> kronrod_abscissae(31);
  kronrod_abscissae[0] = (FloatType)0.999484410050490637571325895705811L;
  kronrod_abscissae[1] = (FloatType)0.996893484074649540271630050918695L;
  kronrod_abscissae[2] = (FloatType)0.991630996870404594858628366109486L;
  kronrod_abscissae[3] = (FloatType)0.983668123279747209970032581605663L;
  kronrod_abscissae[4] = (FloatType)0.973116322501126268374693868423707L;
  kronrod_abscissae[5] = (FloatType)0.960021864968307512216871025581798L;
  kronrod_abscissae[6] = (FloatType)0.944374444748559979415831324037439L;
  kronrod_abscissae[7] = (FloatType)0.926200047429274325879324277080474L;
  kronrod_abscissae[8] = (FloatType)0.905573307699907798546522558925958L;
  kronrod_abscissae[9] = (FloatType)0.882560535792052681543116462530226L;
  kronrod_abscissae[10] = (FloatType)0.857205233546061098958658510658944L;
  kronrod_abscissae[11] = (FloatType)0.829565762382768397442898119732502L;
  kronrod_abscissae[12] = (FloatType)0.799727835821839083013668942322683L;
  kronrod_abscissae[13] = (FloatType)0.767777432104826194917977340974503L;
  kronrod_abscissae[14] = (FloatType)0.733790062453226804726171131369528L;
  kronrod_abscissae[15] = (FloatType)0.697850494793315796932292388026640L;
  kronrod_abscissae[16] = (FloatType)0.660061064126626961370053668149271L;
  kronrod_abscissae[17] = (FloatType)0.620526182989242861140477556431189L;
  kronrod_abscissae[18] = (FloatType)0.579345235826361691756024932172540L;
  kronrod_abscissae[19] = (FloatType)0.536624148142019899264169793311073L;
  kronrod_abscissae[20] = (FloatType)0.492480467861778574993693061207709L;
  kronrod_abscissae[21] = (FloatType)0.447033769538089176780609900322854L;
  kronrod_abscissae[22] = (FloatType)0.400401254830394392535476211542661L;
  kronrod_abscissae[23] = (FloatType)0.352704725530878113471037207089374L;
  kronrod_abscissae[24] = (FloatType)0.304073202273625077372677107199257L;
  kronrod_abscissae[25] = (FloatType)0.254636926167889846439805129817805L;
  kronrod_abscissae[26] = (FloatType)0.204525116682309891438957671002025L;
  kronrod_abscissae[27] = (FloatType)0.153869913608583546963794672743256L;
  kronrod_abscissae[28] = (FloatType)0.102806937966737030147096751318001L;
  kronrod_abscissae[29] = (FloatType)0.051471842555317695833025213166723L;
  kronrod_abscissae[30] = (FloatType)0.000000000000000000000000000000000L;

  return kronrod_abscissae;
}

} // end Utility namespace

#endif // end UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodQuadratureSetTraits_def.hpp
//---------------------------------------------------------------------------//
