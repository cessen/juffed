#include "SelectFilesDlg.h"

#include "Log.h"

#include <QApplication>
#include <QListWidgetItem>

SelectFilesDlg::SelectFilesDlg(const QStringList& files, QWidget* parent) : QDialog(parent) {
	ui_.setupUi(this);
	ui_.textL->setText(tr("Please select files you'd like to save."));
	
	connect(ui_.selectAllChk, SIGNAL(clicked()), SLOT(onAllClicked()));
	connect(ui_.fileList, SIGNAL(itemChanged(QListWidgetItem*)),
	        SLOT(onItemChanged(QListWidgetItem*)));
	
	foreach (QString fileName, files) {
		QListWidgetItem* item = new QListWidgetItem(fileName);
		item->setToolTip(fileName);
		item->setData(Qt::UserRole + 1, fileName);
		item->setCheckState(Qt::Unchecked);
		ui_.fileList->addItem(item);
	}
	
	QApplication::setActiveWindow(this);
}

QStringList SelectFilesDlg::checkedFiles() const {
	QStringList list;

	int count = ui_.fileList->count();
	for (int i = 0; i < count; ++i) {
		QListWidgetItem* item = ui_.fileList->item(i);
		if ( item->checkState() == Qt::Checked ) {
			list << item->data(Qt::UserRole + 1).toString();
		}
	}
	return list;
}

void SelectFilesDlg::accept() {
	QDialog::accept();
}

void SelectFilesDlg::reject() {
	QDialog::reject();
}

void SelectFilesDlg::onAllClicked() {
	int count = ui_.fileList->count();
	bool isChecked = ui_.selectAllChk->checkState() == Qt::Checked;
	
	for (int i = 0; i < count; ++i) {
		QListWidgetItem* item = ui_.fileList->item(i);
		item->setCheckState( isChecked ? Qt::Checked : Qt::Unchecked );
	}
}

void SelectFilesDlg::onItemChanged(QListWidgetItem* item) {
	LOGGER;
	
	if ( item->checkState() == Qt::Unchecked ) {
		ui_.selectAllChk->setChecked(false);
	}
	else {
		int count = ui_.fileList->count();
		bool allChecked = true;
		for (int i = 0; i < count; ++i) {
			QListWidgetItem* item = ui_.fileList->item(i);
			if ( item->checkState() == Qt::Unchecked ) {
				allChecked = false;
				break;
			}
		}
		if ( allChecked ) {
			ui_.selectAllChk->setChecked(true);
		}
	}
}