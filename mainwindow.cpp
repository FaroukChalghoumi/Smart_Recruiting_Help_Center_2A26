#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employes.h"
#include "widget.h"
#include "ui_widget.h"
#include "qrcode.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTextDocument>
#include <QTextStream>
#include <QComboBox>
#include <QTabWidget>
#include"QDate"
#include <QDebug>
#include <list>
#include<qrwidget.h>

#include <QTextBrowser>
#include<QSystemTrayIcon>
#include<QPainter>
#include<QPdfWriter>
#include <QFileDialog>
#include <QFile>
#include <string>
#include <vector>
#include<QDirModel>
#include <qrcode.h>

#include <iostream>
#include <fstream>
#include <QtSvg/QSvgRenderer>
#include <string>
#include <vector>
#include<QDirModel>
#include <qrcode.h>


#include <iostream>
#include <fstream>
#include <QtSvg/QSvgRenderer>

#include "entreprise.h"
#include <QIntValidator>

using namespace std;
using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    employes e;
    ui->tableView->setModel(e.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}



void MainWindow::on_valider_clicked()
{


       int id = ui->id->text().toInt();
       QString nom = ui->nom->text();
       QString prenom = ui->prenom->text();
       int cin = ui->cin->text().toInt();
       QString ddn = ui->ddn->text();
      float salaire = ui->salaire->text().toFloat(); //toFloat
       employes e(id,nom,prenom,cin,ddn,salaire) ;
bool controle=e.controle_saisie();
bool control=e.controle_saisie_champ();

bool controln=e.verifnom(nom);
bool controlp=e.verifnom(prenom);

  bool test;
if( (controle==false) || (control==false) || (controlp==false) || (controln==false) ) {
    QMessageBox::information(nullptr, QObject::tr(""),
                             QObject::tr("Cin doit etre 8 chiffres \n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     }

else{
test=e.ajouter();
if(test)
{

        QMessageBox::information(nullptr, QObject::tr("Ajouter un employe"),
                                 QObject::tr("employe ajouté.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tableView->setModel(e.afficher());

    }
    else {



        QMessageBox::critical(nullptr, QObject::tr("Ajouter un employe"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
ui->id->setText("");
ui->nom->setText("");
ui->prenom->setText("");
ui->cin->setText("");

ui->salaire->setText("");
}









void MainWindow::on_pushButton_5_clicked()
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
            query->prepare("SELECT id from employes");
             query->exec();
             model->setQuery(*query);
             ui->comboBox->setModel(model);

}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{

    QString id=arg1;
     QSqlQueryModel *model= new QSqlQueryModel();
         QSqlQuery   *query= new QSqlQuery();
         query->prepare("SELECT * from employes where id='"+id+"'");
         if(query->exec())
         {
             while (query->next())
             {
                 QString date_string_on_db =query->value(4).toString();
                                 QDate Date = QDate::fromString(date_string_on_db,"dd/MM/yyyy");
                 ui->Mid->setText(query->value(0).toString());
                 ui->Mnom->setText(query->value(1).toString());
                 ui->Mprenom->setText(query->value(2).toString());
                 ui->Mcin->setText(query->value(3).toString());
                  ui->Mddn->setDate(Date);
                   ui->Msalaire->setText(query->value(5).toString());

             }
         }
         model->setQuery(*query);
}



void MainWindow::on_pushButton_7_clicked()
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
            query->prepare("SELECT id from employes");
             query->exec();
             model->setQuery(*query);
             ui->comboBox_2->setModel(model);
}

void MainWindow::on_supprimer_2_clicked()
{
    employes e;
            e.setid(ui->comboBox_2->currentText().toInt());

            bool test;
            test=e.supprime();
            if(test)
            { ui->tableView->setModel(e.afficher());
                QMessageBox::information(nullptr, QObject::tr("supp avec succes"),
                                           QObject::tr("sup successful.\n"
                                                       "Click Cancel to exit."), QMessageBox::Cancel);
            }
                           else
                               QMessageBox::critical(nullptr, QObject::tr("sup errer"),
                                           QObject::tr("sup failed.\n"
                                                       "Click Cancel to exit."), QMessageBox::Cancel);
}







void MainWindow::on_Valider_2_clicked()
{
    employes e;
            e.setid(ui->Mid->text().toInt());
            e.setnom(ui->Mnom->text());
            e.setprenom(ui->Mprenom->text());
            e.setcin(ui->Mcin->text().toInt());
            e.setddn(ui->Mddn->text());
            e.setsalaire(ui->Msalaire->text().toFloat());
            bool test=e.modifier(e.getid(),e.getnom(),e.getprenom(),e.getcin(),e.getddn(),e.getsalaire());
            bool controle=e.controle_saisie();
            bool control=e.controle_saisie_champ();

            bool controln=e.verifnom(e.getnom());
            bool controlp=e.verifnom(e.getprenom());
            if((controle==false)||(control==false) || (controln==false) || ( controlp==false))
            { QMessageBox::information(nullptr, QObject::tr("cin doit etre 8 chiffres"),
                                      QObject::tr("ou un champs manquant.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel); }
            else {
          if(test)
           {  ui->tableView->setModel(e.afficher());
              QMessageBox::information(nullptr, QObject::tr("modifier avec succes"),
                                         QObject::tr("update successful.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);

                     }
                         else
                             QMessageBox::critical(nullptr, QObject::tr("modifier errer"),
                                         QObject::tr("update failed.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);

}
}




void MainWindow::on_Ccin_clicked()
{
    employes e;
    QString A=ui->lineEdit->text();
    ui->tableView->setModel(e.rechercherCin(A));

    if(A=="")
            ui->tableView->setModel(e.afficher());
}




void MainWindow::on_Tid_clicked()
{
    //QString y;
    employes e;
    //y="";

  ui->tableView->setModel(e.trid());
}

void MainWindow::on_Cid_clicked()
{
    employes e;
    QString A=ui->lineEdit->text();
    ui->tableView->setModel(e.rechercherid(A));
}



void MainWindow::on_Cprenom_clicked()
{
    employes e;
    QString A=ui->lineEdit->text();
    ui->tableView->setModel(e.rechercherP(A));

}

void MainWindow::on_actualiser_clicked()
{
    employes e;
    ui->tableView->setModel(e.afficher());
}


void MainWindow::on_Tcin_clicked()
{
    //QString y;
    employes e;
    //y="";

  ui->tableView->setModel(e.tric());
}




void MainWindow::on_Tprenom_clicked()
{

        //QString y;
        employes e;
        //y="";

      ui->tableView->setModel(e.tri());

}



void MainWindow::on_PDF_clicked()
{
    QPdfWriter pdf("C:\\Users\\Mouad\\Documents\\recrucentre\\Employe.pdf");
    QPainter painter(&pdf);
    int i = 5000;
   /* painter.setPen(Qt::yellow);
    painter.setFont(QFont("Time New Roman", 25)); // lfont
    painter.drawText(6000,2500,"recruiting centre dqjfj"); */



QModelIndex index;
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25)); // lfont
    painter.drawText(3000,1400,"Employe");
    painter.setPen(Qt::black); // lkhat
    painter.setFont(QFont("Time New Roman", 15)); // lfont mtaa lktbiba loutaneya
    painter.drawRect(100,100,9400,2500); // rectangle li fih lektiba
    painter.drawRect(100,3000,9400,9000); //rectangle sghir li fih lektiba ***
    painter.setFont(QFont("Time New Roman", 10)); // lkhat mtaa asgher kaaba
    painter.drawText(500,3300,"ID");
    painter.drawText(2500,3300,":");
    painter.drawText(500,3600,"NOM");
    painter.drawText(2500,3600,":");
    painter.drawText(500,3900,"PRENOM");
    painter.drawText(2500,3900,":");
    painter.drawText(500,4200,"CIN");
    painter.drawText(2500,4200,":");
    painter.drawText(500,4500,"Date de naissance");
    painter.drawText(2500,4500,":");
    painter.drawText(500,4800,"salaire");
    painter.drawText(2500,4800,":");
    painter.drawRect(100,3000,9400,9000);
    painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:\\Users\\Mouad\\Documents\\recrucentre\\logo.png"));
    QString aux= on_tableView_clicked(index);

    QSqlQuery query;
    query.prepare("select * from employes WHERE (id LIKE '%"+aux+"%')");
    query.exec();

    while (query.next())
    {
        painter.drawText(3500,3300,query.value(0).toString());
        painter.drawText(3500,3600,query.value(1).toString());
        painter.drawText(3500,3900,query.value(2).toString());
        painter.drawText(3500,4200,query.value(3).toString());
        painter.drawText(3500,4500,query.value(4).toString());
        painter.drawText(3500,4800,query.value(5).toString());

       //i = i + 350;
    }
    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
    QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);




}

/*email::email(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::email)
{
    ui->setupUi(this);
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
}*/


/*void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("adress@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("adress@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("adress@esprit.tn",ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent"){
        QMessageBox::warning( nullptr, tr( "SMTP" ), tr( "Message sent \n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();}
}


*/

QString MainWindow::on_tableView_clicked( const QModelIndex &index)
{
        int id=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
        QString res=QString::number(id);

        /*int num_tel=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),5)).toInt();
        QString res1=QString::number(num_tel);
        ui->lineEdit_Num_tel->setText(res1);
        QVariant nom=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),1));
        QString resN=nom.toString();
        ui->lineEdit_nom->setText(resN);
        QVariant prenom=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),2));
        QString resP=prenom.toString();
        ui->lineEdit_Prenom->setText(resP);
        QVariant mail=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),4));
        QString resM=mail.toString();
        ui->lineEdit_adress_mail->setText(resM);
        int nbre_visites=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),6)).toInt();
        ui->spinBox_nbre_visite->setValue(nbre_visites);
        QVariant date=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),3));
        QString resD=date.toString();
        QDate Date = QDate::fromString(resD,"dd/MM/yyyy");
        ui->dateEdit->setDate(Date);*/
        return res;


}

/*void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void email::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void email::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

email::~email()
{
    delete ui;
}
*/


/*void MainWindow::paintQR(QPainter &painter, const QSize sz, const QString &data, QColor fg)
{
    // NOTE: At this point you will use the API to get the encoding and format you want, instead of my hardcoded stuff:
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(data.toUtf8().constData(), qrcodegen::QrCode::Ecc::LOW);
    const int s=qr.getSize()>0?qr.getSize():1;
    const double w=sz.width();
    const double h=sz.height();
    const double aspect=w/h;
    const double size=((aspect>1.0)?h:w);
    const double scale=size/(s+2);
    // NOTE: For performance reasons my implementation only draws the foreground parts in supplied color.
    // It expects background to be prepared already (in white or whatever is preferred).
    painter.setPen(Qt::NoPen);
    painter.setBrush(fg);
    for(int y=0; y<s; y++) {
        for(int x=0; x<s; x++) {
            const int color=qr.getModule(x, y);  // 0 for white, 1 for black
            if(0!=color) {
                const double rx1=(x+1)*scale, ry1=(y+1)*scale;
                QRectF r(rx1, ry1, scale, scale);
                painter.drawRects(&r,1);
            }
        }
    }
}
*/

/*void MainWindow::on_id_textEdited(const QString &arg1)
{
    ui->QRCODE_2->setQRData(arg1);
}*/

//void MainWindow::on_id_textChanged(const QString &arg1)
//{
  //ui->QRCODE_2->setQRData(arg1);
//}

/*void MainWindow::on_cin_textEdited(const QString &arg1)
{
    ui->QRCODE_2->setQRData(arg1);
} */



void MainWindow::on_Mnom_textEdited(const QString &arg1)
{
    ui->QRCODE->setQRData(arg1);
}

void MainWindow::on_nom_textEdited(const QString &arg1)
{
    ui->QRCODE_2->setQRData(arg1);
}

void MainWindow::on_pushButton_2_clicked()
{
   ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_pushButton_3_clicked()
{
    if(ui->tableView->currentIndex().row()==-1)
               QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                        QObject::tr("Veuillez Choisir un animal du Tableau.\n"
                                                    "Click Ok to exit."), QMessageBox::Ok);
           else
           {

                int id=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
                const QrCode qr = QrCode::encodeText(std::to_string(id).c_str(), QrCode::Ecc::LOW);
                std::ofstream myfile;
                myfile.open ("qrcode.svg") ;
                myfile << qr.toSvgString(1);
                myfile.close();
                QSvgRenderer svgRenderer(QString("qrcode.svg"));
                QPixmap pix( QSize(90, 90) );
                QPainter pixPainter( &pix );
                svgRenderer.render( &pixPainter );
                ui->QRCODE_3->setPixmap(pix);
           }
}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{


    ui->id->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
    ui->nom->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
     ui->prenom->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString());
      ui->cin->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toString());
       ui->salaire->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),4)).toString());


}


void MainWindow::on_lineEdit_2_textEdited(const QString &arg1)
{
    employes e;
    ui->tableView->setModel(e.rechercher1(arg1));
}

void MainWindow::on_pushButton_4_clicked()
{
    Widget w ;
    w.setModal(true);
    w.exec();
}



void MainWindow::sendMaile()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSente(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}







void MainWindow::on_sendBtn_clicked()
{
    sendMaile();
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_exitBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Module_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Module_entreprise_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->afficher->setModel(e.afficher());

}

void MainWindow::on_Farouk_return_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Valider_mod_farouk_clicked()
{

    int id = ui->le_id_farouk->text().toInt();
    int num = ui->le_num_farouk->text().toInt();
    QString nom_entreprise = ui->le_nom_farouk->text();
    QString adress = ui->le_adress_farouk->text();
    QString adressmail = ui->le_adressmail_farouk->text();
    //QDate date = ui->dateEdit->date();
   // Entreprise e (id , num , nom_entreprise , adress , adressmail , date , "contrat");
    Entreprise e (id , num , nom_entreprise , adress , adressmail  , "contrat");


    bool test = e.ajouter();

    if(test)
    {
        ui->afficher->setModel(e.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Ajout effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout non effectuée"),
                    QObject::tr("Ajout non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->stackedWidget->setCurrentIndex(0);
}

/*void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}*/

void MainWindow::on_Ajouter_farouk_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->le_id_farouk->setValidator( new QIntValidator(0, 99999999, this));
    ui->le_num_farouk->setValidator( new QIntValidator(0, 99999999, this));
}

void MainWindow::on_supprimer_farouk_clicked()
{
    int id=ui->le_supprimer_farouk->text().toInt();
    bool test=e.supprimer(id);

    if(test)
    {
         ui->afficher->setModel(e.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_Modifier_farouk_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_Modifier_farouk_2_clicked()
{
    bool    test;
    int id = ui->le_id_2->text().toInt();
    int num = ui->le_num_2->text().toInt();
    QString nom_entreprise = ui->le_nom_2->text();
    QString adress = ui->le_adress_2->text();
    QString adressmail = ui->le_adressmail_2->text();
     test =  e.modifier (id , num , nom_entreprise , adress , adressmail  , "contrat");

          if (test)
          {
                  ui->afficher->setModel(e.afficher());
              QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("modification établie"),
                                   QMessageBox::Ok);}
          else{
          QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                  QObject::tr("modification non établie"),
                                  QMessageBox::Cancel);}
          ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_Trie_botton_clicked()
{
    ui->afficher->setModel(e.sortid_down());
}

void MainWindow::on_Tri_nom_clicked()
{
    ui->afficher->setModel(e.sortname());
}

void MainWindow::on_Tri_adresse_clicked()
{
    ui->afficher->setModel(e.sortadress());
}

void MainWindow::on_rechercheID_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
                   QSqlQuery   *query= new QSqlQuery();
           if(ui->rechercheID->text()==arg1)
                   {
               query->prepare("SELECT * FROM ENTREPRISES WHERE ID_ENTREPRISE LIKE'"+arg1+"%'");//
       query->exec();
           model->setQuery(*query);
       ui->afficher->setModel(model);
}
}

void MainWindow::on_rechercheNom_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
                   QSqlQuery   *query= new QSqlQuery();
           if(ui->rechercheNom->text()==arg1)
                   {
               query->prepare("SELECT * FROM ENTREPRISES WHERE NOM_ENTREPRISE LIKE'"+arg1+"%'");//
       query->exec();
           model->setQuery(*query);
       ui->afficher->setModel(model);
}
}

void MainWindow::on_rechercheAdresse_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
                   QSqlQuery   *query= new QSqlQuery();
           if(ui->rechercheAdresse->text()==arg1)
                   {
               query->prepare("SELECT * FROM ENTREPRISES WHERE COLUMN3 LIKE'"+arg1+"%'");//
       query->exec();
           model->setQuery(*query);
       ui->afficher->setModel(model);
}
}

void MainWindow::on_Email_farouk_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}

void MainWindow::on_Map_farouk_clicked()
{
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();
}