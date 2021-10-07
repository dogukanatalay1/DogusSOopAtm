#include <iostream>
#include <string>

using namespace std;
//---------------------------
class Hesap{
private:
    //private attribute
    string kullaniciAdi;
    string sifre;
    int bakiye;
public:
    //setters
    void setuserName(string isim){
        kullaniciAdi = isim;
    }
    void setpassword(string sf){
        sifre = sf;
    }
    void setbalance(int b){
        bakiye = b;
    }
    //getters
    int getbalance(){
        return bakiye;
    }
    string getuserName(){
        return kullaniciAdi;
    }
    string getpassword(){
        return sifre;
    }
    //Construcktor
    Hesap (string x,string y,int z){
        kullaniciAdi = x;
        sifre = y;
        bakiye = z;
    }
};
//---------------------------
class Login{
    //gelen hesab ile şifreyi bağ daştırıp atm'nin çalışmasını sağlayan method
public:
    bool sifreKontrol(Hesap hesap){
        int girisHakki;
        girisHakki = 3;// kullanıcıya 3 defa yanılma hakkı tanındı.

        while(girisHakki != 0){
            string girilenSifre;
            cout << "Lutfen sifrenizi giriniz: ";
            getline (cin, girilenSifre);
            if(girilenSifre == hesap.getpassword()){
                return true;
            }
            else {
                girisHakki--;
                cout << "Kalan giris hakkınız: "<< girisHakki;
            }
        }
        return false;
    }
};

//---------------------------
class ATM{
    //atm'deki işlemlerin olduğu nokta

public:
    void calis(Hesap hesap){
        Login login;
        if (login.sifreKontrol(hesap)) {//login kontrolü
            while (true) {//5 çıkış işlemi yapılasaya kadar break yapacak program
                string secilenIslem;

                cout << "Islemler:\n1-Bakiye Ogrenme\n2-Para Cekme\n3-Para Yatirma\n4-Dolar alma\n5-Cikis\n"; //işlemler
                cout << "Lutfen yapmak istediginiz islemi seciniz:"; //seçilen işlem'in duyurusu
                getline(cin, secilenIslem);

                if(secilenIslem=="1"){
                    cout << "Bakiyeniz: " << hesap.getbalance();// bakiye sorgulama
                    continue;
                }
                else if(secilenIslem=="2"){
                    int cekilenTutar;
                    geriDon:
                    cout << "Cekmek istediginiz tutarı giriniz...\n";
                    cin >> cekilenTutar;
                    if(cekilenTutar>2000){
                        cout << "Bir gunde 2000tl'den fazlası cekilemez.\n";
                        goto geriDon;
                    }
                    else if(cekilenTutar <=2000){
                        cout << "Isleminiz yapiliyor...\n";
                        hesap.setbalance(hesap.getbalance()-cekilenTutar);
                        cout << "Yeni bakiyeniz: " << hesap.getbalance();
                        continue;
                    }
                    else{
                        cout << "Gecerli bir tutar giriniz...";
                        goto geriDon;
                    }
                }
                else if (secilenIslem=="3"){
                    int yatirilanTutar;
                    cout << "Yatirmak istediginiz tutarı giriniz: ";
                    cin >> yatirilanTutar;
                    hesap.setbalance(hesap.getbalance()+yatirilanTutar);
                    cout << "Yeni bakiyeniz: " << hesap.getbalance();
                }
                else if (secilenIslem=="4"){
                    dolarBasi:
                    int alinanDolar;
                    cout << "Hesabinizdaki para ile " << (hesap.getbalance()/8.87) << " Dolar alabilirsiniz\n";
                    cout << "Almak istediginiz dolar tutarini giriniz: ";
                    cin >> alinanDolar;
                    if (alinanDolar*8.87>hesap.getbalance()){
                        goto dolarBasi;
                    }
                    else if (alinanDolar*8.87 <= hesap.getbalance()){
                        cout << "Isleminiz yapiliyor..";
                        hesap.setbalance(hesap.getbalance()-alinanDolar*8.87);
                        cout << "Yeni bakiyeniz: " << hesap.getbalance();
                        continue;
                    }
                    else{
                        cout << "Lutfen gecerli bir tutar giriniz.";
                        goto dolarBasi;
                    }
                }
                else if (secilenIslem == "5"){
                    cout << "Programdan cikiliyor...";
                    break;
                }
            }
        }
        else{
            cout << "Kart iade ediliyor...\n";
        }
    }
};
//---------------------------
int main() {
    ATM atm;
    Hesap hesap1("Dogus Atalay","1234",1200);
    Hesap hesap2("Anakin Skywalker","66",3000);
    Hesap hesap3("Laz Ziya","6161",200000);

    string girilenAd;

    Hesap Hesaplar[3] = {hesap1,hesap2,hesap3};
    cout << "Kullanici adinizi giriniz: ";
    getline (cin, girilenAd);

    for(int i=0; i<3;i++){
        Hesap temp = Hesaplar[i];
        if (girilenAd == temp.getuserName()){
            atm.calis(temp);
        }
        else {
            continue;
        }
    }
}
//---------------------------
