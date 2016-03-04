//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodQuadratureSetTraits.cpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod quadrature set traits 
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GaussKronrodQuadratureSetTraits.hpp"


namespace Utility{

    /******************* 15 point rule *******************/
    // Gauss quadrature weights 
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<15>::gauss_weights =
        GaussKronrodQuadratureSetTraits<15>::initializeGaussWeights();
    
    // Kronrad quadrature weights 
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<15>::kronrod_weights = 
        GaussKronrodQuadratureSetTraits<15>::initializeKronrodWeights();

    // Kronrad quadrature abscissae
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<15>::kronrod_abscissae =
        GaussKronrodQuadratureSetTraits<15>::initializeKronrodAbscissae();

    // Initialize the gauss weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<15>::initializeGaussWeights()
    { 
        Teuchos::Array<double> gauss_weights(4);
        gauss_weights[0] = 0.129484966168869693270611432679082;
        gauss_weights[1] = 0.279705391489276667901467771423780;
        gauss_weights[2] = 0.381830050505118944950369775488975;
        gauss_weights[3] = 0.417959183673469387755102040816327;

        return gauss_weights;
    }

    // Initialize the kronrod weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<15>::initializeKronrodWeights()
    {
        Teuchos::Array<double> kronrod_weights(8);
        kronrod_weights[0] = 0.022935322010529224963732008058970;
        kronrod_weights[1] = 0.063092092629978553290700663189204;
        kronrod_weights[2] = 0.104790010322250183839876322541518;
        kronrod_weights[3] = 0.140653259715525918745189590510238;
        kronrod_weights[4] = 0.169004726639267902826583426598550;
        kronrod_weights[5] = 0.190350578064785409913256402421014;
        kronrod_weights[6] = 0.204432940075298892414161999234649;
        kronrod_weights[7] = 0.209482141084727828012999174891714;

        return kronrod_weights;
    }

    // Initialize the gauss weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<15>::initializeKronrodAbscissae()
    {
        Teuchos::Array<double> kronrod_abscissae(8);
        kronrod_abscissae[0] = 0.991455371120812639206854697526329;
        kronrod_abscissae[1] = 0.949107912342758524526189684047851;
        kronrod_abscissae[2] = 0.864864423359769072789712788640926;
        kronrod_abscissae[3] = 0.741531185599394439863864773280788;
        kronrod_abscissae[4] = 0.586087235467691130294144838258730;
        kronrod_abscissae[5] = 0.405845151377397166906606412076961;
        kronrod_abscissae[6] = 0.207784955007898467600689403773245;
        kronrod_abscissae[7] = 0.000000000000000000000000000000000;

        return kronrod_abscissae;
    }


    /******************* 21 point rule *******************/
    // Gauss quadrature weights 
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<21>::gauss_weights =
        GaussKronrodQuadratureSetTraits<21>::initializeGaussWeights();
    
    // Kronrad quadrature weights 
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<21>::kronrod_weights = 
        GaussKronrodQuadratureSetTraits<21>::initializeKronrodWeights();

    // Kronrad quadrature abscissae
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<21>::kronrod_abscissae =
        GaussKronrodQuadratureSetTraits<21>::initializeKronrodAbscissae();

    // Initialize the gauss weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<21>::initializeGaussWeights()
    { 
        Teuchos::Array<double> gauss_weights(5);
        gauss_weights[0] = 0.066671344308688137593568809893332;
        gauss_weights[1] = 0.149451349150580593145776339657697;
        gauss_weights[2] = 0.219086362515982043995534934228163;
        gauss_weights[3] = 0.269266719309996355091226921569469;
        gauss_weights[4] = 0.295524224714752870173892994651338;

        return gauss_weights;
    }

    // Initialize the kronrod weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<21>::initializeKronrodWeights()
    {
        Teuchos::Array<double> kronrod_weights(11);
        kronrod_weights[0] = 0.011694638867371874278064396062192;
        kronrod_weights[1] = 0.032558162307964727478818972459390;
        kronrod_weights[2] = 0.054755896574351996031381300244580;
        kronrod_weights[3] = 0.075039674810919952767043140916190;
        kronrod_weights[4] = 0.093125454583697605535065465083366;
        kronrod_weights[5] = 0.109387158802297641899210590325805;
        kronrod_weights[6] = 0.123491976262065851077958109831074;
        kronrod_weights[7] = 0.134709217311473325928054001771707;
        kronrod_weights[8] = 0.142775938577060080797094273138717;
        kronrod_weights[9] = 0.147739104901338491374841515972068;
        kronrod_weights[10] = 0.149445554002916905664936468389821;

        return kronrod_weights;
    }

    // Initialize the gauss weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<21>::initializeKronrodAbscissae()
    {
        Teuchos::Array<double> kronrod_abscissae(11);
        kronrod_abscissae[0] = 0.995657163025808080735527280689003;
        kronrod_abscissae[1] = 0.973906528517171720077964012084452;
        kronrod_abscissae[2] = 0.930157491355708226001207180059508;
        kronrod_abscissae[3] = 0.865063366688984510732096688423493;
        kronrod_abscissae[4] = 0.780817726586416897063717578345042;
        kronrod_abscissae[5] = 0.679409568299024406234327365114874;
        kronrod_abscissae[6] = 0.562757134668604683339000099272694;
        kronrod_abscissae[7] = 0.433395394129247190799265943165784;
        kronrod_abscissae[8] = 0.294392862701460198131126603103866;
        kronrod_abscissae[9] = 0.148874338981631210884826001129720;
        kronrod_abscissae[10] = 0.000000000000000000000000000000000;

        return kronrod_abscissae;
    }


    /******************* 31 point rule *******************/
    // Gauss quadrature weights 
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<31>::gauss_weights =
        GaussKronrodQuadratureSetTraits<31>::initializeGaussWeights();
    
    // Kronrad quadrature weights 
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<31>::kronrod_weights = 
        GaussKronrodQuadratureSetTraits<31>::initializeKronrodWeights();

    // Kronrad quadrature abscissae
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<31>::kronrod_abscissae =
        GaussKronrodQuadratureSetTraits<31>::initializeKronrodAbscissae();

    // Initialize the gauss weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<31>::initializeGaussWeights()
    { 
        Teuchos::Array<double> gauss_weights(8);
        gauss_weights[0] = 0.030753241996117268354628393577204;
        gauss_weights[1] = 0.070366047488108124709267416450667;
        gauss_weights[2] = 0.107159220467171935011869546685869;
        gauss_weights[3] = 0.139570677926154314447804794511028;
        gauss_weights[4] = 0.166269205816993933553200860481209;
        gauss_weights[5] = 0.186161000015562211026800561866423;
        gauss_weights[6] = 0.198431485327111576456118326443839;
        gauss_weights[7] = 0.202578241925561272880620199967519;

        return gauss_weights;
    }

    // Initialize the kronrod weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<31>::initializeKronrodWeights()
    {
        Teuchos::Array<double> kronrod_weights(16);
        kronrod_weights[0] = 0.005377479872923348987792051430128;
        kronrod_weights[1] = 0.015007947329316122538374763075807;
        kronrod_weights[2] = 0.025460847326715320186874001019653;
        kronrod_weights[3] = 0.035346360791375846222037948478360;
        kronrod_weights[4] = 0.044589751324764876608227299373280;
        kronrod_weights[5] = 0.053481524690928087265343147239430;
        kronrod_weights[6] = 0.062009567800670640285139230960803;
        kronrod_weights[7] = 0.069854121318728258709520077099147;
        kronrod_weights[8] = 0.076849680757720378894432777482659;
        kronrod_weights[9] = 0.083080502823133021038289247286104;
        kronrod_weights[10] = 0.088564443056211770647275443693774;
        kronrod_weights[11] = 0.093126598170825321225486872747346;
        kronrod_weights[12] = 0.096642726983623678505179907627589;
        kronrod_weights[13] = 0.099173598721791959332393173484603;
        kronrod_weights[14] = 0.100769845523875595044946662617570;
        kronrod_weights[15] = 0.101330007014791549017374792767493;

        return kronrod_weights;
    }

    // Initialize the gauss weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<31>::initializeKronrodAbscissae()
    {
        Teuchos::Array<double> kronrod_abscissae(16);
        kronrod_abscissae[0] = 0.998002298693397060285172840152271;
        kronrod_abscissae[1] = 0.987992518020485428489565718586613;
        kronrod_abscissae[2] = 0.967739075679139134257347978784337;
        kronrod_abscissae[3] = 0.937273392400705904307758947710209;
        kronrod_abscissae[4] = 0.897264532344081900882509656454496;
        kronrod_abscissae[5] = 0.848206583410427216200648320774217;
        kronrod_abscissae[6] = 0.790418501442465932967649294817947;
        kronrod_abscissae[7] = 0.724417731360170047416186054613938;
        kronrod_abscissae[8] = 0.650996741297416970533735895313275;
        kronrod_abscissae[9] = 0.570972172608538847537226737253911;
        kronrod_abscissae[10] = 0.485081863640239680693655740232351;
        kronrod_abscissae[11] = 0.394151347077563369897207370981045;
        kronrod_abscissae[12] = 0.299180007153168812166780024266389;
        kronrod_abscissae[13] = 0.201194093997434522300628303394596;
        kronrod_abscissae[14] = 0.101142066918717499027074231447392;
        kronrod_abscissae[15] = 0.000000000000000000000000000000000;

        return kronrod_abscissae;
    }


    /******************* 41 point rule *******************/
    // Gauss quadrature weights 
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<41>::gauss_weights =
        GaussKronrodQuadratureSetTraits<41>::initializeGaussWeights();
    
    // Kronrad quadrature weights 
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<41>::kronrod_weights = 
        GaussKronrodQuadratureSetTraits<41>::initializeKronrodWeights();

    // Kronrad quadrature abscissae
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<41>::kronrod_abscissae =
        GaussKronrodQuadratureSetTraits<41>::initializeKronrodAbscissae();

    // Initialize the gauss weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<41>::initializeGaussWeights()
    { 
        Teuchos::Array<double> gauss_weights(10);
        gauss_weights[0] = 0.017614007139152118311861962351853;
        gauss_weights[1] = 0.040601429800386941331039952274932;
        gauss_weights[2] = 0.062672048334109063569506535187042;
        gauss_weights[3] = 0.083276741576704748724758143222046;
        gauss_weights[4] = 0.101930119817240435036750135480350;
        gauss_weights[5] = 0.118194531961518417312377377711382;
        gauss_weights[6] = 0.131688638449176626898494499748163;
        gauss_weights[7] = 0.142096109318382051329298325067165;
        gauss_weights[8] = 0.149172986472603746787828737001969;
        gauss_weights[9] = 0.152753387130725850698084331955098;

        return gauss_weights;
    }

    // Initialize the kronrod weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<41>::initializeKronrodWeights()
    {
        Teuchos::Array<double> kronrod_weights(21);
        kronrod_weights[0] = 0.003073583718520531501218293246031;
        kronrod_weights[1] = 0.008600269855642942198661787950102;
        kronrod_weights[2] = 0.014626169256971252983787960308868;
        kronrod_weights[3] = 0.020388373461266523598010231432755;
        kronrod_weights[4] = 0.025882133604951158834505067096153;
        kronrod_weights[5] = 0.031287306777032798958543119323801;
        kronrod_weights[6] = 0.036600169758200798030557240707211;
        kronrod_weights[7] = 0.041668873327973686263788305936895;
        kronrod_weights[8] = 0.046434821867497674720231880926108;
        kronrod_weights[9] = 0.050944573923728691932707670050345;
        kronrod_weights[10] = 0.055195105348285994744832372419777;
        kronrod_weights[11] = 0.059111400880639572374967220648594;
        kronrod_weights[12] = 0.062653237554781168025870122174255;
        kronrod_weights[13] = 0.065834597133618422111563556969398;
        kronrod_weights[14] = 0.068648672928521619345623411885368;
        kronrod_weights[15] = 0.071054423553444068305790361723210;
        kronrod_weights[16] = 0.073030690332786667495189417658913;
        kronrod_weights[17] = 0.074582875400499188986581418362488;
        kronrod_weights[18] = 0.075704497684556674659542775376617;
        kronrod_weights[19] = 0.076377867672080736705502835038061;
        kronrod_weights[20] = 0.076600711917999656445049901530102;

        return kronrod_weights;
    }

    // Initialize the gauss weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<41>::initializeKronrodAbscissae()
    {
        Teuchos::Array<double> kronrod_abscissae(21);
        kronrod_abscissae[0] = 0.998859031588277663838315576545863;
        kronrod_abscissae[1] = 0.993128599185094924786122388471320;
        kronrod_abscissae[2] = 0.981507877450250259193342994720217;
        kronrod_abscissae[3] = 0.963971927277913791267666131197277;
        kronrod_abscissae[4] = 0.940822633831754753519982722212443;
        kronrod_abscissae[5] = 0.912234428251325905867752441203298;
        kronrod_abscissae[6] = 0.878276811252281976077442995113078;
        kronrod_abscissae[7] = 0.839116971822218823394529061701521;
        kronrod_abscissae[8] = 0.795041428837551198350638833272788;
        kronrod_abscissae[9] = 0.746331906460150792614305070355642;
        kronrod_abscissae[10] = 0.693237656334751384805490711845932;
        kronrod_abscissae[11] = 0.636053680726515025452836696226286;
        kronrod_abscissae[12] = 0.575140446819710315342946036586425;
        kronrod_abscissae[13] = 0.510867001950827098004364050955251;
        kronrod_abscissae[14] = 0.443593175238725103199992213492640;
        kronrod_abscissae[15] = 0.373706088715419560672548177024927;
        kronrod_abscissae[16] = 0.301627868114913004320555356858592;
        kronrod_abscissae[17] = 0.227785851141645078080496195368575;
        kronrod_abscissae[18] = 0.152605465240922675505220241022678;
        kronrod_abscissae[19] = 0.076526521133497333754640409398838;
        kronrod_abscissae[20] = 0.000000000000000000000000000000000;

        return kronrod_abscissae;
    }


    /******************* 51 point rule *******************/
    // Gauss quadrature weights 
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<51>::gauss_weights =
        GaussKronrodQuadratureSetTraits<51>::initializeGaussWeights();
    
    // Kronrad quadrature weights 
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<51>::kronrod_weights = 
        GaussKronrodQuadratureSetTraits<51>::initializeKronrodWeights();

    // Kronrad quadrature abscissae
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<51>::kronrod_abscissae =
        GaussKronrodQuadratureSetTraits<51>::initializeKronrodAbscissae();

    // Initialize the gauss weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<51>::initializeGaussWeights()
    { 
        Teuchos::Array<double> gauss_weights(13);
        gauss_weights[0] = 0.011393798501026287947902964113235;
        gauss_weights[1] = 0.026354986615032137261901815295299;
        gauss_weights[2] = 0.040939156701306312655623487711646;
        gauss_weights[3] = 0.054904695975835191925936891540473;
        gauss_weights[4] = 0.068038333812356917207187185656708;
        gauss_weights[5] = 0.080140700335001018013234959669111;
        gauss_weights[6] = 0.091028261982963649811497220702892;
        gauss_weights[7] = 0.100535949067050644202206890392686;
        gauss_weights[8] = 0.108519624474263653116093957050117;
        gauss_weights[9] = 0.114858259145711648339325545869556;
        gauss_weights[10] = 0.119455763535784772228178126512901;
        gauss_weights[11] = 0.122242442990310041688959518945852;
        gauss_weights[12] = 0.123176053726715451203902873079050;

        return gauss_weights;
    }

    // Initialize the kronrod weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<51>::initializeKronrodWeights()
    {
        Teuchos::Array<double> kronrod_weights(26);
        kronrod_weights[0] = 0.001987383892330315926507851882843;
        kronrod_weights[1] = 0.005561932135356713758040236901066;
        kronrod_weights[2] = 0.009473973386174151607207710523655;
        kronrod_weights[3] = 0.013236229195571674813656405846976;
        kronrod_weights[4] = 0.016847817709128298231516667536336;
        kronrod_weights[5] = 0.020435371145882835456568292235939;
        kronrod_weights[6] = 0.024009945606953216220092489164881;
        kronrod_weights[7] = 0.027475317587851737802948455517811;
        kronrod_weights[8] = 0.030792300167387488891109020215229;
        kronrod_weights[9] = 0.034002130274329337836748795229551;
        kronrod_weights[10] = 0.037116271483415543560330625367620;
        kronrod_weights[11] = 0.040083825504032382074839284467076;
        kronrod_weights[12] = 0.042872845020170049476895792439495;
        kronrod_weights[13] = 0.045502913049921788909870584752660;
        kronrod_weights[14] = 0.047982537138836713906392255756915;
        kronrod_weights[15] = 0.050277679080715671963325259433440;
        kronrod_weights[16] = 0.052362885806407475864366712137873;
        kronrod_weights[17] = 0.054251129888545490144543370459876;
        kronrod_weights[18] = 0.055950811220412317308240686382747;
        kronrod_weights[19] = 0.057437116361567832853582693939506;
        kronrod_weights[20] = 0.058689680022394207961974175856788;
        kronrod_weights[21] = 0.059720340324174059979099291932562;
        kronrod_weights[22] = 0.060539455376045862945360267517565;
        kronrod_weights[23] = 0.061128509717053048305859030416293;
        kronrod_weights[24] = 0.061471189871425316661544131965264;
        kronrod_weights[25] = 0.061580818067832935078759824240066;

        return kronrod_weights;
    }

    // Initialize the gauss weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<51>::initializeKronrodAbscissae()
    {
        Teuchos::Array<double> kronrod_abscissae(26);
        kronrod_abscissae[0] = 0.999262104992609834193457486540341;
        kronrod_abscissae[1] = 0.995556969790498097908784946893902;
        kronrod_abscissae[2] = 0.988035794534077247637331014577406;
        kronrod_abscissae[3] = 0.976663921459517511498315386479594;
        kronrod_abscissae[4] = 0.961614986425842512418130033660167;
        kronrod_abscissae[5] = 0.942974571228974339414011169658471;
        kronrod_abscissae[6] = 0.920747115281701561746346084546331;
        kronrod_abscissae[7] = 0.894991997878275368851042006782805;
        kronrod_abscissae[8] = 0.865847065293275595448996969588340;
        kronrod_abscissae[9] = 0.833442628760834001421021108693570;
        kronrod_abscissae[10] = 0.797873797998500059410410904994307;
        kronrod_abscissae[11] = 0.759259263037357630577282865204361;
        kronrod_abscissae[12] = 0.717766406813084388186654079773298;
        kronrod_abscissae[13] = 0.673566368473468364485120633247622;
        kronrod_abscissae[14] = 0.626810099010317412788122681624518;
        kronrod_abscissae[15] = 0.577662930241222967723689841612654;
        kronrod_abscissae[16] = 0.526325284334719182599623778158010;
        kronrod_abscissae[17] = 0.473002731445714960522182115009192;
        kronrod_abscissae[18] = 0.417885382193037748851814394594572;
        kronrod_abscissae[19] = 0.361172305809387837735821730127641;
        kronrod_abscissae[20] = 0.303089538931107830167478909980339;
        kronrod_abscissae[21] = 0.243866883720988432045190362797452;
        kronrod_abscissae[22] = 0.183718939421048892015969888759528;
        kronrod_abscissae[23] = 0.122864692610710396387359818808037;
        kronrod_abscissae[24] = 0.061544483005685078886546392366797;
        kronrod_abscissae[25] = 0.000000000000000000000000000000000;

        return kronrod_abscissae;
    }


    /******************* 61 point rule *******************/
    // Gauss quadrature weights 
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<61>::gauss_weights =
        GaussKronrodQuadratureSetTraits<61>::initializeGaussWeights();
    
    // Kronrad quadrature weights 
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<61>::kronrod_weights = 
        GaussKronrodQuadratureSetTraits<61>::initializeKronrodWeights();

    // Kronrad quadrature abscissae
    const Teuchos::Array<double> GaussKronrodQuadratureSetTraits<61>::kronrod_abscissae =
        GaussKronrodQuadratureSetTraits<61>::initializeKronrodAbscissae();

    // Initialize the gauss weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<61>::initializeGaussWeights()
    { 
        Teuchos::Array<double> gauss_weights(15);
        gauss_weights[0] = 0.007968192496166605615465883474674;
        gauss_weights[1] = 0.018466468311090959142302131912047;
        gauss_weights[2] = 0.028784707883323369349719179611292;
        gauss_weights[3] = 0.038799192569627049596801936446348;
        gauss_weights[4] = 0.048402672830594052902938140422808;
        gauss_weights[5] = 0.057493156217619066481721689402056;
        gauss_weights[6] = 0.065974229882180495128128515115962;
        gauss_weights[7] = 0.073755974737705206268243850022191;
        gauss_weights[8] = 0.080755895229420215354694938460530;
        gauss_weights[9] = 0.086899787201082979802387530715126;
        gauss_weights[10] = 0.092122522237786128717632707087619;
        gauss_weights[11] = 0.096368737174644259639468626351810;
        gauss_weights[12] = 0.099593420586795267062780282103569;
        gauss_weights[13] = 0.101762389748405504596428952168554;
        gauss_weights[14] = 0.102852652893558840341285636705415;

        return gauss_weights;
    }

    // Initialize the kronrod weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<61>::initializeKronrodWeights()
    {
        Teuchos::Array<double> kronrod_weights(31);
        kronrod_weights[0] = 0.001389013698677007624551591226760;
        kronrod_weights[1] = 0.003890461127099884051267201844516;
        kronrod_weights[2] = 0.006630703915931292173319826369750;
        kronrod_weights[3] = 0.009273279659517763428441146892024;
        kronrod_weights[4] = 0.011823015253496341742232898853251;
        kronrod_weights[5] = 0.014369729507045804812451432443580;
        kronrod_weights[6] = 0.016920889189053272627572289420322;
        kronrod_weights[7] = 0.019414141193942381173408951050128;
        kronrod_weights[8] = 0.021828035821609192297167485738339;
        kronrod_weights[9] = 0.024191162078080601365686370725232;
        kronrod_weights[10] = 0.026509954882333101610601709335075;
        kronrod_weights[11] = 0.028754048765041292843978785354334;
        kronrod_weights[12] = 0.030907257562387762472884252943092;
        kronrod_weights[13] = 0.032981447057483726031814191016854;
        kronrod_weights[14] = 0.034979338028060024137499670731468;
        kronrod_weights[15] = 0.036882364651821229223911065617136;
        kronrod_weights[16] = 0.038678945624727592950348651532281;
        kronrod_weights[17] = 0.040374538951535959111995279752468;
        kronrod_weights[18] = 0.041969810215164246147147541285970;
        kronrod_weights[19] = 0.043452539701356069316831728117073;
        kronrod_weights[20] = 0.044814800133162663192355551616723;
        kronrod_weights[21] = 0.046059238271006988116271735559374;
        kronrod_weights[22] = 0.047185546569299153945261478181099;
        kronrod_weights[23] = 0.048185861757087129140779492298305;
        kronrod_weights[24] = 0.049055434555029778887528165367238;
        kronrod_weights[25] = 0.049795683427074206357811569379942;
        kronrod_weights[26] = 0.050405921402782346840893085653585;
        kronrod_weights[27] = 0.050881795898749606492297473049805;
        kronrod_weights[28] = 0.051221547849258772170656282604944;
        kronrod_weights[29] = 0.051426128537459025933862879215781;
        kronrod_weights[30] = 0.051494729429451567558340433647099;

        return kronrod_weights;
    }

    // Initialize the gauss weight array
    Teuchos::Array<double> GaussKronrodQuadratureSetTraits<61>::initializeKronrodAbscissae()
    {
        Teuchos::Array<double> kronrod_abscissae(31);
        kronrod_abscissae[0] = 0.999484410050490637571325895705811;
        kronrod_abscissae[1] = 0.996893484074649540271630050918695;
        kronrod_abscissae[2] = 0.991630996870404594858628366109486;
        kronrod_abscissae[3] = 0.983668123279747209970032581605663;
        kronrod_abscissae[4] = 0.973116322501126268374693868423707;
        kronrod_abscissae[5] = 0.960021864968307512216871025581798;
        kronrod_abscissae[6] = 0.944374444748559979415831324037439;
        kronrod_abscissae[7] = 0.926200047429274325879324277080474;
        kronrod_abscissae[8] = 0.905573307699907798546522558925958;
        kronrod_abscissae[9] = 0.882560535792052681543116462530226;
        kronrod_abscissae[10] = 0.857205233546061098958658510658944;
        kronrod_abscissae[11] = 0.829565762382768397442898119732502;
        kronrod_abscissae[12] = 0.799727835821839083013668942322683;
        kronrod_abscissae[13] = 0.767777432104826194917977340974503;
        kronrod_abscissae[14] = 0.733790062453226804726171131369528;
        kronrod_abscissae[15] = 0.697850494793315796932292388026640;
        kronrod_abscissae[16] = 0.660061064126626961370053668149271;
        kronrod_abscissae[17] = 0.620526182989242861140477556431189;
        kronrod_abscissae[18] = 0.579345235826361691756024932172540;
        kronrod_abscissae[19] = 0.536624148142019899264169793311073;
        kronrod_abscissae[20] = 0.492480467861778574993693061207709;
        kronrod_abscissae[21] = 0.447033769538089176780609900322854;
        kronrod_abscissae[22] = 0.400401254830394392535476211542661;
        kronrod_abscissae[23] = 0.352704725530878113471037207089374;
        kronrod_abscissae[24] = 0.304073202273625077372677107199257;
        kronrod_abscissae[25] = 0.254636926167889846439805129817805;
        kronrod_abscissae[26] = 0.204525116682309891438957671002025;
        kronrod_abscissae[27] = 0.153869913608583546963794672743256;
        kronrod_abscissae[28] = 0.102806937966737030147096751318001;
        kronrod_abscissae[29] = 0.051471842555317695833025213166723;
        kronrod_abscissae[30] = 0.000000000000000000000000000000000;

        return kronrod_abscissae;
    }

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodQuadratureSetTraits.cpp
//---------------------------------------------------------------------------//
