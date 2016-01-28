//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodIntegration_def.hpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod integration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_INTEGRATION_DEF_HPP
#define UTILITY_GAUSS_KRONROD_INTEGRATION_DEF_HPP

// Std Includes
#include <limits>

// GSL Includes
#include <gsl/gsl_errno.h>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_ConstTypeTraits.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_IntegrationException.hpp"
#include "Utility_SortAlgorithms.hpp"

namespace Utility{

/*
// Gauss-Kronrod quadrature set for 15 point rule
template<>
struct GaussKronrodIntegration::QuadratureSet<15>
{
  // Valid rule
  static const bool valid_rule = true;

  // Gauss quadrature weights 
  static const double gauss_weights[4] =
  {
    0.129484966168869693270611432679082,
    0.279705391489276667901467771423780,
    0.381830050505118944950369775488975,
    0.417959183673469387755102040816327
  };
    
  // Kronrad quadrature weights 
  static const double kronrod_weights[8] = 
  {
    0.022935322010529224963732008058970,
    0.063092092629978553290700663189204,
    0.104790010322250183839876322541518,
    0.140653259715525918745189590510238,
    0.169004726639267902826583426598550,
    0.190350578064785409913256402421014,
    0.204432940075298892414161999234649,
    0.209482141084727828012999174891714
  };

  // Kronrad quadrature abscissae
  static const double kronrod_abscissae[8] = 
  {
    0.991455371120812639206854697526329,
    0.949107912342758524526189684047851,
    0.864864423359769072789712788640926,
    0.741531185599394439863864773280788,
    0.586087235467691130294144838258730,
    0.405845151377397166906606412076961,
    0.207784955007898467600689403773245,
    0.000000000000000000000000000000000
  };
};

// Gauss-Kronrod quadrature set for 21 point rule
template<>
struct GaussKronrodIntegration::QuadratureSet<21>
{
  //! Valid rule
  static const bool valid_rule = true;

  // Gauss quadrature weights 
  const double gauss_weights[5] =
  {
    0.066671344308688137593568809893332,
    0.149451349150580593145776339657697,
    0.219086362515982043995534934228163,
    0.269266719309996355091226921569469,
    0.295524224714752870173892994651338
  };

  // Kronrad quadrature weights 
  const double kronrod_weights[11] = 
  {
    0.011694638867371874278064396062192,
    0.032558162307964727478818972459390,
    0.054755896574351996031381300244580,
    0.075039674810919952767043140916190,
    0.093125454583697605535065465083366,
    0.109387158802297641899210590325805,
    0.123491976262065851077958109831074,
    0.134709217311473325928054001771707,
    0.142775938577060080797094273138717,
    0.147739104901338491374841515972068,
    0.149445554002916905664936468389821
 };

  // Kronrad quadrature abscissae
  const double kronrod_abscissae[11] = 
  {
    0.995657163025808080735527280689003,
    0.973906528517171720077964012084452,
    0.930157491355708226001207180059508,
    0.865063366688984510732096688423493,
    0.780817726586416897063717578345042,
    0.679409568299024406234327365114874,
    0.562757134668604683339000099272694,
    0.433395394129247190799265943165784,
    0.294392862701460198131126603103866,
    0.148874338981631210884826001129720,
    0.000000000000000000000000000000000
  };
};

// Gauss-Kronrod quadrature set for 31 point rule
template<>
struct GaussKronrodIntegration::QuadratureSet<31>
{
  //! Valid rule
  static const bool valid_rule = true;

  // Gauss quadrature weights 
  const double gauss_weights[8] =
  {
    0.030753241996117268354628393577204,
    0.070366047488108124709267416450667,
    0.107159220467171935011869546685869,
    0.139570677926154314447804794511028,
    0.166269205816993933553200860481209,
    0.186161000015562211026800561866423,
    0.198431485327111576456118326443839,
    0.202578241925561272880620199967519
  };

  // Kronrad quadrature weights 
  const double kronrod_weights[16] = 
  {
    0.005377479872923348987792051430128,
    0.015007947329316122538374763075807,
    0.025460847326715320186874001019653,
    0.035346360791375846222037948478360,
    0.044589751324764876608227299373280,
    0.053481524690928087265343147239430,
    0.062009567800670640285139230960803,
    0.069854121318728258709520077099147,
    0.076849680757720378894432777482659,
    0.083080502823133021038289247286104,
    0.088564443056211770647275443693774,
    0.093126598170825321225486872747346,
    0.096642726983623678505179907627589,
    0.099173598721791959332393173484603,
    0.100769845523875595044946662617570,
    0.101330007014791549017374792767493
   };

  // Kronrad quadrature abscissae
  const double kronrod_abscissae[16] = 
  {
    0.998002298693397060285172840152271,
    0.987992518020485428489565718586613,
    0.967739075679139134257347978784337,
    0.937273392400705904307758947710209,
    0.897264532344081900882509656454496,
    0.848206583410427216200648320774217,
    0.790418501442465932967649294817947,
    0.724417731360170047416186054613938,
    0.650996741297416970533735895313275,
    0.570972172608538847537226737253911,
    0.485081863640239680693655740232351,
    0.394151347077563369897207370981045,
    0.299180007153168812166780024266389,
    0.201194093997434522300628303394596,
    0.101142066918717499027074231447392,
    0.000000000000000000000000000000000
  };
};

// Gauss-Kronrod quadrature set for 41 point rule
template<>
struct GaussKronrodIntegration::QuadratureSet<41>
{
  //! Valid rule
  static const bool valid_rule = true;

  // Gauss quadrature weights 
  const double gauss_weights[11] =
  {
    0.017614007139152118311861962351853,
    0.040601429800386941331039952274932,
    0.062672048334109063569506535187042,
    0.083276741576704748724758143222046,
    0.101930119817240435036750135480350,
    0.118194531961518417312377377711382,
    0.131688638449176626898494499748163,
    0.142096109318382051329298325067165,
    0.149172986472603746787828737001969,
    0.152753387130725850698084331955098
  };

  // Kronrad quadrature weights 
  const double kronrod_weights[21] = 
  {
    0.003073583718520531501218293246031,
    0.008600269855642942198661787950102,
    0.014626169256971252983787960308868,
    0.020388373461266523598010231432755,
    0.025882133604951158834505067096153,
    0.031287306777032798958543119323801,
    0.036600169758200798030557240707211,
    0.041668873327973686263788305936895,
    0.046434821867497674720231880926108,
    0.050944573923728691932707670050345,
    0.055195105348285994744832372419777,
    0.059111400880639572374967220648594,
    0.062653237554781168025870122174255,
    0.065834597133618422111563556969398,
    0.068648672928521619345623411885368,
    0.071054423553444068305790361723210,
    0.073030690332786667495189417658913,
    0.074582875400499188986581418362488,
    0.075704497684556674659542775376617,
    0.076377867672080736705502835038061,
    0.076600711917999656445049901530102
   };

  // Kronrad quadrature abscissae
  const double kronrod_abscissae[21] = 
  {
    0.998859031588277663838315576545863,
    0.993128599185094924786122388471320,
    0.981507877450250259193342994720217,
    0.963971927277913791267666131197277,
    0.940822633831754753519982722212443,
    0.912234428251325905867752441203298,
    0.878276811252281976077442995113078,
    0.839116971822218823394529061701521,
    0.795041428837551198350638833272788,
    0.746331906460150792614305070355642,
    0.693237656334751384805490711845932,
    0.636053680726515025452836696226286,
    0.575140446819710315342946036586425,
    0.510867001950827098004364050955251,
    0.443593175238725103199992213492640,
    0.373706088715419560672548177024927,
    0.301627868114913004320555356858592,
    0.227785851141645078080496195368575,
    0.152605465240922675505220241022678,
    0.076526521133497333754640409398838,
    0.000000000000000000000000000000000
  };
};

// Gauss-Kronrod quadrature set for 51 point rule
template<>
struct GaussKronrodIntegration::QuadratureSet<51>
{
  //! Valid rule
  static const bool valid_rule = true;

  // Gauss quadrature weights 
  const double gauss_weights[13] =
  {
  0.011393798501026287947902964113235,
  0.026354986615032137261901815295299,
  0.040939156701306312655623487711646,
  0.054904695975835191925936891540473,
  0.068038333812356917207187185656708,
  0.080140700335001018013234959669111,
  0.091028261982963649811497220702892,
  0.100535949067050644202206890392686,
  0.108519624474263653116093957050117,
  0.114858259145711648339325545869556,
  0.119455763535784772228178126512901,
  0.122242442990310041688959518945852,
  0.123176053726715451203902873079050
  };

  // Kronrad quadrature weights 
  const double kronrod_weights[26] = 
  {
    0.001987383892330315926507851882843,
    0.005561932135356713758040236901066,
    0.009473973386174151607207710523655,
    0.013236229195571674813656405846976,
    0.016847817709128298231516667536336,
    0.020435371145882835456568292235939,
    0.024009945606953216220092489164881,
    0.027475317587851737802948455517811,
    0.030792300167387488891109020215229,
    0.034002130274329337836748795229551,
    0.037116271483415543560330625367620,
    0.040083825504032382074839284467076,
    0.042872845020170049476895792439495,
    0.045502913049921788909870584752660,
    0.047982537138836713906392255756915,
    0.050277679080715671963325259433440,
    0.052362885806407475864366712137873,
    0.054251129888545490144543370459876,
    0.055950811220412317308240686382747,
    0.057437116361567832853582693939506,
    0.058689680022394207961974175856788,
    0.059720340324174059979099291932562,
    0.060539455376045862945360267517565,
    0.061128509717053048305859030416293,
    0.061471189871425316661544131965264,
    0.061580818067832935078759824240066
   };

  // Kronrad quadrature abscissae
  const double kronrod_abscissae[26] = 
  {
    0.999262104992609834193457486540341,
    0.995556969790498097908784946893902,
    0.988035794534077247637331014577406,
    0.976663921459517511498315386479594,
    0.961614986425842512418130033660167,
    0.942974571228974339414011169658471,
    0.920747115281701561746346084546331,
    0.894991997878275368851042006782805,
    0.865847065293275595448996969588340,
    0.833442628760834001421021108693570,
    0.797873797998500059410410904994307,
    0.759259263037357630577282865204361,
    0.717766406813084388186654079773298,
    0.673566368473468364485120633247622,
    0.626810099010317412788122681624518,
    0.577662930241222967723689841612654,
    0.526325284334719182599623778158010,
    0.473002731445714960522182115009192,
    0.417885382193037748851814394594572,
    0.361172305809387837735821730127641,
    0.303089538931107830167478909980339,
    0.243866883720988432045190362797452,
    0.183718939421048892015969888759528,
    0.122864692610710396387359818808037,
    0.061544483005685078886546392366797,
    0.000000000000000000000000000000000
  };
};

// Gauss-Kronrod quadrature set for 61 point rule
template<>
struct GaussKronrodIntegration::QuadratureSet<61>
{
  //! Valid rule
  static const bool valid_rule = true;

  // Gauss quadrature weights 
  const double gauss_weights[15] =
  {
    0.007968192496166605615465883474674,
    0.018466468311090959142302131912047,
    0.028784707883323369349719179611292,
    0.038799192569627049596801936446348,
    0.048402672830594052902938140422808,
    0.057493156217619066481721689402056,
    0.065974229882180495128128515115962,
    0.073755974737705206268243850022191,
    0.080755895229420215354694938460530,
    0.086899787201082979802387530715126,
    0.092122522237786128717632707087619,
    0.096368737174644259639468626351810,
    0.099593420586795267062780282103569,
    0.101762389748405504596428952168554,
    0.102852652893558840341285636705415
  };

  // Kronrad quadrature weights 
  const double kronrod_weights[31] = 
  {
    0.001389013698677007624551591226760,
    0.003890461127099884051267201844516,
    0.006630703915931292173319826369750,
    0.009273279659517763428441146892024,
    0.011823015253496341742232898853251,
    0.014369729507045804812451432443580,
    0.016920889189053272627572289420322,
    0.019414141193942381173408951050128,
    0.021828035821609192297167485738339,
    0.024191162078080601365686370725232,
    0.026509954882333101610601709335075,
    0.028754048765041292843978785354334,
    0.030907257562387762472884252943092,
    0.032981447057483726031814191016854,
    0.034979338028060024137499670731468,
    0.036882364651821229223911065617136,
    0.038678945624727592950348651532281,
    0.040374538951535959111995279752468,
    0.041969810215164246147147541285970,
    0.043452539701356069316831728117073,
    0.044814800133162663192355551616723,
    0.046059238271006988116271735559374,
    0.047185546569299153945261478181099,
    0.048185861757087129140779492298305,
    0.049055434555029778887528165367238,
    0.049795683427074206357811569379942,
    0.050405921402782346840893085653585,
    0.050881795898749606492297473049805,
    0.051221547849258772170656282604944,
    0.051426128537459025933862879215781,
    0.051494729429451567558340433647099
   };

  // Kronrad quadrature abscissae
  const double kronrod_abscissae[31] = 
  {
    0.999484410050490637571325895705811,
    0.996893484074649540271630050918695,
    0.991630996870404594858628366109486,
    0.983668123279747209970032581605663,
    0.973116322501126268374693868423707,
    0.960021864968307512216871025581798,
    0.944374444748559979415831324037439,
    0.926200047429274325879324277080474,
    0.905573307699907798546522558925958,
    0.882560535792052681543116462530226,
    0.857205233546061098958658510658944,
    0.829565762382768397442898119732502,
    0.799727835821839083013668942322683,
    0.767777432104826194917977340974503,
    0.733790062453226804726171131369528,
    0.697850494793315796932292388026640,
    0.660061064126626961370053668149271,
    0.620526182989242861140477556431189,
    0.579345235826361691756024932172540,
    0.536624148142019899264169793311073,
    0.492480467861778574993693061207709,
    0.447033769538089176780609900322854,
    0.400401254830394392535476211542661,
    0.352704725530878113471037207089374,
    0.304073202273625077372677107199257,
    0.254636926167889846439805129817805,
    0.204525116682309891438957671002025,
    0.153869913608583546963794672743256,
    0.102806937966737030147096751318001,
    0.051471842555317695833025213166723,
    0.000000000000000000000000000000000
  };
};
*/
// Function wrapper for evaluating the functor
template<typename Functor>
double GaussKronrodIntegration::functorWrapper( const double x, 
						     void* indirected_functor )
{
  // Make sure the functor is valid
  testPrecondition( indirected_functor );

  Functor* functor = (Functor*)( indirected_functor );

  return (*functor)( x );
}

// Integrate the function adaptively
/*! \details Functor must have operator()( double ) defined. This function
 * applies the specified integration rule (Points) adaptively until an 
 * estimate of the integral of the integrand over [lower_limit,upper_limit] is
 * achieved within the desired tolerances. Valid Gauss-Kronrod rules are
 * 15, 21, 31, 41, 51 and 61. Higher-order rules give better accuracy for
 * smooth functions, while lower-order rules save time when the function
 * contains local difficulties, such as discontinuities. On each iteration
 * the adaptive integration strategy bisects the interval with the largest
 * error estimate. See the qag function details in the quadpack documentation.
 */ 
template<int Points, typename Functor>
void GaussKronrodIntegration::integrateAdaptively(
						 Functor& integrand, 
						 double lower_limit, 
						 double upper_limit,
						 double& result,
						 double& absolute_error ) const
{
 
  Teuchos::Array<double> bin_result( d_subinterval_limit ); 
  Teuchos::Array<double> bin_error( d_subinterval_limit );
  Teuchos::Array<double> bin_lower_limit( d_subinterval_limit );
  Teuchos::Array<double> bin_upper_limit( d_subinterval_limit );
  Teuchos::Array<double> bin_order( d_subinterval_limit );

  int error_type;

  bin_lower_limit[0] = lower_limit;
  bin_upper_limit[0] = upper_limit;  

  if ( d_absolute_error_tol <= 0 && 
      (d_relative_error_tol < 50 * std::numeric_limits<double>::epsilon() ||
       d_relative_error_tol < 0.5e-28))
    {
      std::cout << 
      "tolerance cannot be acheived with given absolute and relative error tolerance" <<
      std::endl;
    }

  /* perform the first integration */

  double result_abs, result_asc;

  integrateWithPointRule<Points>( 
    integrand, 
    lower_limit, 
    upper_limit, 
    bin_result[0], 
    bin_error[0], 
    result_abs, 
    result_asc );

  /* Test on accuracy */

  double tolerance = 
    std::max(d_absolute_error_tol, d_relative_error_tol * fabs (bin_result[0]));

  double round_off = 50.0*std::numeric_limits<double>::epsilon()*result_abs;

  if (absolute_error <= round_off && absolute_error > tolerance)
    {
      std::cout << "cannot reach tolerance because of roundoff error "
                   "on first attempt" << std::endl;
 
      result = bin_result[0];
      absolute_error = bin_error[0];     

      return;
    }
  else if ( ( absolute_error <= tolerance && absolute_error != result_asc ) || 
            absolute_error == 0.0)
    {
      result = bin_result[0];
      absolute_error = bin_error[0];    

      return;
    }
  else if (d_subinterval_limit == 1)
    {
      std::cout << "a maximum of one iteration was insufficient" << std::endl;

      result = bin_result[0];
      absolute_error = bin_error[0];    

      return;
    }

  double maximum_bin_error = bin_error[0];
  int bin_with_max_error = 0;
  double area = bin_result[0];
  double total_error = bin_error[0];
  double round_off_1 = 0.0;
  double round_off_2 = 0.0;
  int nr_max = 0;

  int last;
  for ( last = 2; last < d_subinterval_limit; last++ )
    {
      double lower_limit_1, upper_limit_1, lower_limit_2, upper_limit_2;
      double Lower_limit_i, upper_limit_i, result_i, error_i;
      double area_1 = 0, area_2 = 0, area_12 = 0;
      double error_1 = 0, error_2 = 0, error_12 = 0;
      double result_asc_1, result_asc_2;
      double result_abs_1, result_abs_2;

      /* Bisect the subinterval with the largest error estimate 
         into interval 1 and 2 */

      lower_limit_1 = bin_lower_limit[bin_with_max_error]; 
      upper_limit_1 = 0.5 * ( bin_lower_limit[bin_with_max_error] + 
                              bin_upper_limit[bin_with_max_error] );
      lower_limit_2 = upper_limit_1;
      upper_limit_2 = bin_upper_limit[bin_with_max_error];

      integrateWithPointRule<Points>( 
        integrand, 
        lower_limit_1, 
        upper_limit_1, 
        area_1, 
        error_1, 
        result_abs_1, 
        result_asc_1 );

      integrateWithPointRule<Points>( 
        integrand, 
        lower_limit_2, 
        upper_limit_2, 
        area_2, 
        error_2, 
        result_abs_2, 
        result_asc_2 );

      /* Improve previous approximations to integral and error and 
         test for accuracy. */

      area_12 = area_1 + area_2;
      error_12 = error_1 + error_2;

      total_error += error_12 - maximum_bin_error;
      area += area_12 - bin_result[bin_with_max_error];

      if (result_asc_1 != error_1 && result_asc_2 != error_2)
        {
          double delta = bin_result[bin_with_max_error] - area_12;

          if ( fabs (delta) <= 1.0e-5 * fabs (area_12) && 
               error_12 >= 0.99 * maximum_bin_error )
            {
              round_off_1++;
            }
          if ( last >= 10 && error_12 > maximum_bin_error )
            {
              round_off_2++;
            }
        }

      bin_result[bin_with_max_error] = area_1;
      bin_result[last] = area_2;

      tolerance = std::max( d_absolute_error_tol, d_relative_error_tol * fabs (area));

      if ( error_type != 0 || total_error <= tolerance )
        break;
      else // Test for roundoff error and eventually set error flag.
      {
        if (round_off_1 >= 6 || round_off_2 >= 20)
        {
          error_type = 2;   /* round off error */
          break;
        }
        else if ( last == d_subinterval_limit )
        {
          /* Set error flag in the case that the number of 
             subintervals equals limit. */
          error_type = 1;
          break;
        }
        else if ( subintervalTooSmall<Points>( lower_limit_1, 
                                               lower_limit_2, 
                                               upper_limit_2 ) )
        {
          /* set error flag in the case of bad integrand behaviour at
             a point of the integration range */
          error_type = 3;
          break;
        }
      }

      updateIntegral( bin_lower_limit, bin_upper_limit, bin_result, bin_error,
                      lower_limit_1, upper_limit_1, area_1, error_1, 
                      lower_limit_2, upper_limit_2, area_2, error_2,
                      last, bin_with_max_error );

      sortErrorList( bin_error, bin_order, maximum_bin_error,
                     bin_with_max_error, last, nr_max );
    }

  for ( int i = 0; i < last; i++ )
    result += bin_result[i];

  absolute_error = total_error;

  if ( error_type == 1 )
    {
      std::cout << "Maximum number of subdivisions reached" << std::endl;
    }
  else if (error_type == 2)
    {
      std::cout << "Roundoff error prevented tolerance from being achieved" << std::endl;
    }
  else if (error_type == 3)
    {
      std::cout << "Bad integrand behavior found in the integration interval" << std::endl;
    }
  else
    {
      std::cout << "could not integrate function" << std::endl;
    }
}

// Integrate the function with given Gauss-Kronrod point rule
/*! \details Functor must have operator()( double ) defined. This function
 * applies the specified integration rule (Points) to estimate 
 * the integral of the integrand over [lower_limit,upper_limit]. 
 * Valid Gauss-Kronrod rules are 15, 21, 31, 41, 51 and 61. 
 * Higher-order rules give better accuracy for smooth functions, 
 * while lower-order rules save time when the function contains local 
 * difficulties, such as discontinuities. On each iteration
 * the adaptive integration strategy bisects the interval with the largest
 * error estimate. See the qag function details in the quadpack documentation.
 */ 
template<int Points, typename Functor>
void GaussKronrodIntegration::integrateWithPointRule(
						 Functor& integrand, 
						 double lower_limit, 
						 double upper_limit,
						 double& result,
						 double& absolute_error,
             double& result_abs, 
             double& result_asc ) const
{
  // Make sure the integration limits are valid
  testPrecondition( lower_limit <= upper_limit );
  // Make sure the integration limits are bounded
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( lower_limit ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( upper_limit ) );

  int number_of_weights = (Points+1)/2;

  double gauss_weights[number_of_weights/2];
  double kronrod_abscissae[number_of_weights];
  double kronrod_weights[number_of_weights];

std::cout << "number_of_weights = " << number_of_weights << std::endl;
std::cout << "number_of_weights = " << number_of_weights << std::endl;
std::cout << "Points = " << Points << std::endl;
  if ( Points == 15 )
  { 
  // Gauss quadrature weights 
  gauss_weights[4] =
  {
    0.129484966168869693270611432679082,
    0.279705391489276667901467771423780,
    0.381830050505118944950369775488975,
    0.417959183673469387755102040816327
  };
    
  // Kronrad quadrature weights 
  kronrod_weights[8] = 
  {
    0.022935322010529224963732008058970,
    0.063092092629978553290700663189204,
    0.104790010322250183839876322541518,
    0.140653259715525918745189590510238,
    0.169004726639267902826583426598550,
    0.190350578064785409913256402421014,
    0.204432940075298892414161999234649,
    0.209482141084727828012999174891714
  };

  // Kronrad quadrature abscissae
  kronrod_abscissae[8] = 
  {
    0.991455371120812639206854697526329,
    0.949107912342758524526189684047851,
    0.864864423359769072789712788640926,
    0.741531185599394439863864773280788,
    0.586087235467691130294144838258730,
    0.405845151377397166906606412076961,
    0.207784955007898467600689403773245,
    0.000000000000000000000000000000000
  };
  }
  else
    testPrecondition( false );

std::cout << "kronrod_weights[0] = " << kronrod_weights[0] << std::endl;
std::cout << "kronrod_weights[1] = " << kronrod_weights[1] << std::endl;
std::cout << "kronrod_weights[2] = " << kronrod_weights[2] << std::endl;
std::cout << "kronrod_weights[3] = " << kronrod_weights[3] << std::endl;


  if( lower_limit < upper_limit )
  {
    // midpoint between upper and lower integration limits
    double midpoint = 0.5*( upper_limit + lower_limit );

    // half the length between the upper and lower integration limits
    double half_length = 0.5*(upper_limit - lower_limit );

    // Integrand at the midpoint
    double integrand_midpoint = integrand( midpoint );

    // Estimate result for Gauss
    double gauss_result = 
        gauss_weights[3]*integrand_midpoint;

    // Estimate result for Kronrod
    double kronrod_result = 
        integrand_midpoint*kronrod_weights[7];
 
    // Absolute value of kronrod estimate
    result_abs = fabs( kronrod_result );

    Teuchos::Array<double> integrand_values_lower( 7 );
    Teuchos::Array<double> integrand_values_upper( 7 );
    Teuchos::Array<double> integrand_values_sum( 7 );

    // Estimate Kronrod and absolute value integral
    for ( int j = 0; j < number_of_weights - 1; j++ )
      {  
        calculateQuadratureIntegrandValuesAtAbscissa( 
            integrand, 
            kronrod_abscissae[j],
            half_length,
            midpoint,
            integrand_values_lower[j],
            integrand_values_upper[j] );

        kronrod_result += 
            kronrod_weights[j]*integrand_values_sum[j];
std::cout << "j  = " << j  << std::endl;
std::cout << "kronrod_weights[j]  = " << kronrod_weights[j]  << std::endl;
std::cout << "integrand_values_sum[j]  = " << integrand_values_sum[j]  << std::endl;
std::cout << "kronrod_result  = " << kronrod_result  << std::endl;

        integrand_values_sum[j] = 
          integrand_values_lower[j] + integrand_values_upper[j];

        result_abs += kronrod_weights[j]*( 
          fabs( integrand_values_lower[j] ) + fabs( integrand_values_upper[j] ) );
      };

    double mean_kronrod_result = 0.5*kronrod_result;
    result_asc = kronrod_weights[7]*
        fabs( integrand_midpoint - mean_kronrod_result );

    for ( int j = 0; j < number_of_weights - 1; j++ )
      {  

        result_asc += kronrod_weights[j]*
          ( fabs( integrand_values_lower[j] - mean_kronrod_result ) +
            fabs( integrand_values_upper[j] - mean_kronrod_result ) );
      };

    // Estimate Gauss integral
    for ( int j = 0; j < ( number_of_weights - 1 )/2; j++ )
      {
        int jj = j*2 + 1;
        gauss_result += 
            gauss_weights[j]*integrand_values_sum[jj];
      };

  double abs_half_length = fabs( half_length );
  result = kronrod_result*half_length;
  result_abs *= abs_half_length;
  result_asc *= abs_half_length;
  absolute_error = fabs( ( kronrod_result - gauss_result ) * half_length );
std::cout << "final kronrod_result  = " << kronrod_result  << std::endl;
std::cout << "absolute_error  = " << absolute_error  << std::endl;
  rescaleAbsoluteError( absolute_error, result_abs, result_asc );
std::cout << "rescaleAbsoluteError  = " << absolute_error  << std::endl;
         


  }
  else if( lower_limit == upper_limit )
  {
    result = 0.0;
    absolute_error = 0.0;
  }
  else // invalid limits
  {
    THROW_EXCEPTION( Utility::IntegrationException,
		     "Invalid integration limits: " << lower_limit << " !< "
		     << upper_limit << "." );
  }
}

// Test if subinterval is too small
template<int Points>
inline bool GaussKronrodIntegration::subintervalTooSmall( 
        double& lower_limit_1, 
        double& lower_limit_2, 
        double& upper_limit_2 ) const
{
  int c = Points/10;
  double max = std::max( fabs ( lower_limit_1 ), fabs ( upper_limit_2 ) );
  double epsilon = 1000.0*c*std::numeric_limits<double>::epsilon();
  double min = 10000.0*std::numeric_limits<double>::min();

//  std::cout << "c = " << c << std::endl;
//  std::cout << "lower_limit_1 = " << lower_limit_1 << std::endl;
//  std::cout << "lower_limit_2 = " << lower_limit_2 << std::endl;
//  std::cout << "upper_limit_2 = " << upper_limit_2 << std::endl;
//  std::cout << "max = " << max << std::endl;
//  std::cout << "epsilon = " << epsilon << std::endl;
//  std::cout << "min = " << min << std::endl;
//  std::cout << "epsilon() = " << std::numeric_limits<double>::epsilon() << std::endl;
//  std::cout << "min() = " << std::numeric_limits<double>::min() << std::endl;

  if ( max <= ( 1.0 + epsilon ) * ( fabs( lower_limit_2 ) + min ) )
    return true;
  else
    return false;
};

// Calculate the quadrature upper and lower integrand values at an abscissa
template<typename Functor>
void GaussKronrodIntegration::calculateQuadratureIntegrandValuesAtAbscissa( 
    Functor& integrand, 
    double abscissa,
    double half_length,
    double midpoint,
    double& integrand_value_lower,
    double& integrand_value_upper ) const
{
  double weighted_abscissa = half_length*abscissa;

  integrand_value_lower = integrand( midpoint - abscissa );
  integrand_value_upper = integrand( midpoint + abscissa );
};  

} // end Utility namespace

#endif // end UTILITY_GAUSS_KRONROD_INTEGRATION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegration_def.hpp
//---------------------------------------------------------------------------//
