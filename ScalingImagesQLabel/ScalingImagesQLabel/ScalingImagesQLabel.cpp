#include "ScalingImagesQLabel.h"
#include <qpainter.h>
#include <qlabel.h>

namespace
{
  class QLabelPixmapScaler : public QObject
  {
  public:
    explicit QLabelPixmapScaler(QLabel *label, Qt::AspectRatioMode aspect_mode)
      : QObject{label}, m_pixmap{*label->pixmap()}, m_aspect_mode{aspect_mode}
    {
      setObjectName("QLabelPixmapScaler");

      // Remove previous scalers, so only one is active
      for (auto prev_scaler : label->findChildren<QLabelPixmapScaler *>(objectName())) {
        label->removeEventFilter(prev_scaler);
      }

      label->installEventFilter(this);
    }

    bool eventFilter(QObject *obj, QEvent *event) override
    {
      if (obj == parent() && event->type() == QEvent::Resize) {
        auto label = (QLabel *)parent();

        // Goal: create a new image that contains the scaled label's pixmap, fitting inside and centered
        auto image = QImage{label->size(), QImage::Format_ARGB32_Premultiplied};
        image.fill(Qt::transparent); // cannot use QPainter::eraseGeometry when working with a QImage as painting device

        // Scale image
        const auto scaled_pixmap = m_pixmap.scaled(label->size(), m_aspect_mode, Qt::SmoothTransformation);

        // Center image by computing the new origin
        const auto size_diff = label->size() - scaled_pixmap.size();
        const auto top_left = QPoint{size_diff.width() / 2, size_diff.height() / 2};

        // Render the new image
        QPainter painter{&image};
        painter.drawPixmap(top_left, scaled_pixmap);
        painter.end();

        // Set the new pixmap of the label
        label->setPixmap(QPixmap::fromImage(image));
      }

      return false;
    }

  private:
    const QPixmap m_pixmap; // copy of the original pixmap to prevent degradation of image after several resizes
    const Qt::AspectRatioMode m_aspect_mode;
  };
}

ScalingImagesQLabel::ScalingImagesQLabel(QWidget *parent) : QMainWindow(parent)
{
  ui.setupUi(this);

  [[maybe_unused]] auto auto_scaler_fit = new QLabelPixmapScaler{ui.imgAutoScale_Fit, Qt::KeepAspectRatio};
  [[maybe_unused]] auto auto_scaler_cover =
    new QLabelPixmapScaler{ui.imgAutoScale_Cover, Qt::KeepAspectRatioByExpanding};
}
