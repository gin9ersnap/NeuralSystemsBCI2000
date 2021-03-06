////////////////////////////////////////////////////////////////////////////////
// $Id$
// Author: juergen.mellinger@uni-tuebingen.de
// Description: A class that represents a display rectangle for a set of
//   GraphObjects.
//
// $BEGIN_BCI2000_LICENSE$
//
// This file is part of BCI2000, a platform for real-time bio-signal research.
// [ Copyright (C) 2000-2012: BCI2000 team and many external contributors ]
//
// BCI2000 is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// BCI2000 is distributed in the hope that it will be useful, but
//                         WITHOUT ANY WARRANTY
// - without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
// $END_BCI2000_LICENSE$
////////////////////////////////////////////////////////////////////////////////
#include "PCHIncludes.h"
#pragma hdrstop

#if USE_QT
# include <QPainter>
# include <QGLWidget>
# include <QImage>
# include <QPixmap>
# include <QPaintEvent>
# include <QMouseEvent>
#endif

#include "GraphDisplay.h"
#include "BitmapImage.h"

#include <algorithm>

using namespace GUI;
using namespace std;

#if USE_QT
namespace GUI
{

class WidgetBase
{
 public:
  WidgetBase( GraphDisplay& );
  virtual ~WidgetBase();
 protected:
  void SetWidget( QWidget* );
  void OnPaintEvent( QPaintEvent* );
  void OnMousePressEvent( QMouseEvent* );
 private:
  GraphDisplay& mrGraphDisplay;
  QWidget*      mpWidget;
};

class GLWidget : public QGLWidget, private WidgetBase
{
 public:
  GLWidget( GraphDisplay& d, const QGLFormat& f, QWidget* p )
    : QGLWidget( f, p ), WidgetBase( d ) { SetWidget( this ); }
 protected:
  void paintEvent( QPaintEvent* e )
    { WidgetBase::OnPaintEvent( e ); }
  void mousePressEvent( QMouseEvent* e )
    { WidgetBase::OnMousePressEvent( e ); }
};

class Widget : public QWidget, private WidgetBase
{
 public:
  Widget( GraphDisplay& d, QWidget* p )
    : QWidget( p ), WidgetBase( d ) { SetWidget( this ); }
 protected:
  void paintEvent( QPaintEvent* e )
    { WidgetBase::OnPaintEvent( e ); }
  void mousePressEvent( QMouseEvent* e )
    { WidgetBase::OnMousePressEvent( e ); }
};

} // namespace GUI
#endif // USE_QT

#if _WIN32
// This function uses StretchBlt() to read only required pixels from
// video memory. Thus, it is considerably faster to use it than using Qt's
// QPixmap::grabWindow() followed with QPixmap::scaled().
static void
BitmapImageFromHDC( BitmapImage& ioImage, HDC inDC, const RECT& inSourceRect )
{
  int width = ioImage.Width(),
      height = ioImage.Height(),
      originalWidth = inSourceRect.right - inSourceRect.left,
      originalHeight = inSourceRect.bottom - inSourceRect.top;
  if( width > 0 && height > 0 && inDC != NULL )
  {
    HDC miniDC = ::CreateCompatibleDC( inDC );
    HBITMAP miniBmp = ::CreateCompatibleBitmap( inDC, width, height );
    ::DeleteObject( ::SelectObject( miniDC, miniBmp ) );
    // STRETCH_DELETESCANS is the only option that ignores intermediate pixels,
    // thus it is the fastest one here.
    ::SetStretchBltMode( miniDC, STRETCH_DELETESCANS );
    ::StretchBlt(
      miniDC, 0, 0, width, height,
      inDC, inSourceRect.left, inSourceRect.top, originalWidth, originalHeight,
      SRCCOPY
    );

    BITMAPINFO info;
    ::memset( &info, 0, sizeof( BITMAPINFO ) );
    info.bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
    info.bmiHeader.biHeight = -height;
    info.bmiHeader.biWidth = width;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = 0;
    uint32_t* pBitmapData = new uint32_t[ width * height ];
    int result = ::GetDIBits(
                     miniDC, miniBmp,
                     0, height,
                     pBitmapData,
                     &info, DIB_RGB_COLORS
                   );
    if( result > 0 )
      for( int x = 0; x < width; ++x )
        for( int y = 0; y < height; ++y )
          ioImage( x, y ) = RGBColor( pBitmapData[ x + y * width ] & 0xffffff );
    delete[] pBitmapData;
    ::DeleteDC( miniDC );
    ::DeleteObject( miniBmp );
  }
}
#endif // _WIN32

#if USE_QT
static void
BitmapImageFromQPixmap( BitmapImage& ioImage, const QPixmap& inPixmap )
{
  int width = ioImage.Width(),
      height = ioImage.Height();
  QImage img( inPixmap.scaled( width, height ).toImage() );
  for( int x = 0; x < width; ++x )
  {
    for( int y = 0; y < height; ++y )
    {
      QColor color = QColor::fromRgba( img.pixel( x, y ) );
      if( color.alpha() == 0 )
        ioImage( x, y ) = RGBColor::NullColor;
      else
        ioImage( x, y ) = RGBColor( color.red(), color.green(), color.blue() );
    }
  }
}
#endif // USE_QT

// GraphDisplay definitions
GraphDisplay::GraphDisplay()
: mColor( RGBColor::Gray )
{
  mContext.rect.left = 0;
  mContext.rect.top = 0;
  mContext.rect.right = 0;
  mContext.rect.bottom = 0;
#if USE_QT
  mContext.handle.device = NULL;
  mContext.handle.painter = NULL;
  mContext.handle.glContext = NULL;
  mpWidget = NULL;
  mUsingGL = false;
#endif
  mpOffscreenBmp = NULL;
}

GraphDisplay::~GraphDisplay()
{
#if USE_QT
  delete mpWidget;
#endif
  ClearOffscreenBuffer();
  DeleteObjects();
}


const GraphDisplay&
GraphDisplay::Update() const
{
#if USE_QT
  if( mpWidget )
    mpWidget->repaint( mInvalidRegion.translated( -mpWidget->pos() ) );
#endif
  return *this;
}

GraphDisplay&
GraphDisplay::Add( GraphObject* inObj )
{
  mObjects.insert( inObj );
  return *this;
}

GraphDisplay&
GraphDisplay::Remove( GraphObject* inObj )
{
  inObj->Invalidate();
  mObjects.erase( inObj );
  mObjectsClicked.remove( inObj );
  if( inObj->NeedsGL() )
    Change();
  return *this;
}

void
GraphDisplay::Change()
{
#if USE_QT
  bool useGL = false;
  for( SetOfGraphObjects::iterator i = mObjects.begin(); i != mObjects.end(); ++i )
    useGL |= ( *i )->NeedsGL();

  if( !useGL && mUsingGL || useGL && !mUsingGL )
  {
    delete mpWidget;
    mpWidget = NULL;
    mContext.handle.glContext = NULL;
  }
  mUsingGL = useGL;

  QWidget* pParent = dynamic_cast<QWidget*>( mContext.handle.device );
  if( mpWidget && mpWidget->parent() != pParent )
  {
    delete mpWidget;
    mpWidget = NULL;
    mContext.handle.glContext = NULL;
  }
  if( pParent && !mpWidget )
  {
    if( useGL )
    {
      QGLFormat format = QGLFormat::defaultFormat();
      format.setDepth( true );
      format.setDepthBufferSize( 16 );
      format.setOverlay( true );
      format.setSwapInterval( 0 ); // disable VSync
      GLWidget* pWidget = new GLWidget( *this, format, pParent );
      if( pWidget->isValid() )
        mpWidget = pWidget;
      else
        delete pWidget;
    }
    else
    {
      mpWidget = new Widget( *this, pParent );
    }
  }
  if( mUsingGL && !mContext.handle.glContext )
  {
    mContext.handle.glContext = dynamic_cast<QGLWidget*>( mpWidget );
  }
  if( mpWidget )
  {
    mpWidget->setGeometry(
      mContext.rect.left,
      mContext.rect.top,
      mContext.rect.right - mContext.rect.left,
      mContext.rect.bottom - mContext.rect.top
    );
  }
#endif // USE_QT
  ClearOffscreenBuffer();
  Invalidate();
  for( SetOfGraphObjects::iterator i = mObjects.begin(); i != mObjects.end(); ++i )
    ( *i )->Change();
}

void
GraphDisplay::Paint( const void* inRegionHandle )
{
#if USE_QT
  int left = static_cast<int>( mContext.rect.left ),
      top = static_cast<int>( mContext.rect.top ),
      width = static_cast<int>( mContext.rect.right - mContext.rect.left ),
      height = static_cast<int>( mContext.rect.bottom - mContext.rect.top );

  if( !mpWidget && mpOffscreenBmp == NULL )
    mpOffscreenBmp = new QPixmap( width, height );

  if( mpOffscreenBmp && mColor == RGBColor::NullColor )
    mpOffscreenBmp->fill( Qt::transparent );

  QPainter* pPainter = mpWidget ? new QPainter( mpWidget ) : new QPainter( mpOffscreenBmp );
  pPainter->translate( -left, -top );
  const QRegion* pInputRegion = reinterpret_cast<const QRegion*>( inRegionHandle );
  if( pInputRegion )
    mInvalidRegion += *pInputRegion;
  pPainter->setClipRegion( mInvalidRegion );
  // Create a rect for the background color
  if( mColor != RGBColor::NullColor )
    pPainter->fillRect(
      QRect( left, top, width, height ),
      QColor( mColor.R(), mColor.G(), mColor.B() )
    );
  mContext.handle.painter = pPainter;
#endif // USE_QT

  vector<GraphObject*> objects( mObjects.begin(), mObjects.end() );
  sort( objects.begin(), objects.end(), GraphObject::CompareByZOrder() );
  for( vector<GraphObject*>::iterator i = objects.begin(); i != objects.end(); ++i )
    ( *i )->Paint();

#if USE_QT
  pPainter->end();
  mContext.handle.painter = NULL;
  delete pPainter;
  mInvalidRegion = QRegion();
#endif
}

void
GraphDisplay::Click( int inX, int inY )
{
  float width = mContext.rect.right - mContext.rect.left,
        height = mContext.rect.bottom - mContext.rect.top;
  GUI::Point p = {
    ( inX - mContext.rect.left ) / width,
    ( inY - mContext.rect.top ) / height
  };
  vector<GraphObject*> objects( mObjects.begin(), mObjects.end() );
  sort( objects.begin(), objects.end(), GraphObject::CompareByZOrder() );
  for( vector<GraphObject*>::iterator i = objects.begin(); i != objects.end(); ++i )
    if( ( *i )->Visible() && ( *i )->Click( p ) )
      mObjectsClicked.push( *i );
}

GraphDisplay&
GraphDisplay::Invalidate()
{
  return InvalidateRect( mContext.rect );
}

GraphDisplay&
GraphDisplay::InvalidateRect( const GUI::Rect& inRect )
{
#if USE_QT
  QRegion rgn(
      static_cast<int>( inRect.left ),
      static_cast<int>( inRect.top ),
      static_cast<int>( inRect.Width() ),
      static_cast<int>( inRect.Height() )
  );
  mInvalidRegion += rgn;
  // On a plain QWidget, we need to call QWidget::update() to make sure
  // the QWidget::repaint() call actually triggers its paintEvent() rather
  // than blitting from its back buffer.
  // For a QGLWidget, paintEvent() is always triggered by QWidget::update()
  // as well as QWidget::repaint(). So we do not call QWidget::update() for
  // a QGLWidget to avoid it being redrawn multiple times.
  if( mpWidget && !mUsingGL )
    mpWidget->update( rgn.translated( -mpWidget->pos() ) );
#endif // USE_QT
  return *this;
}

GUI::Rect
GraphDisplay::NormalizedToPixelCoords( const GUI::Rect& inRect ) const
{
  float width = mContext.rect.right - mContext.rect.left,
        height = mContext.rect.bottom - mContext.rect.top;
  GUI::Rect result =
  {
    mContext.rect.left + width  * inRect.left,
    mContext.rect.top  + height * inRect.top,
    mContext.rect.left + width  * inRect.right,
    mContext.rect.top  + height * inRect.bottom
  };
  return result;
}

GUI::Rect
GraphDisplay::PixelToNormalizedCoords( const GUI::Rect& inRect ) const
{
  const GUI::Rect unitRect = { 0, 0, 1, 1 };
  if( EmptyRect( mContext.rect ) )
    return unitRect;

  float width = mContext.rect.right - mContext.rect.left,
        height = mContext.rect.bottom - mContext.rect.top;
  GUI::Rect result =
  {
    ( inRect.left - mContext.rect.left ) / width,
    ( inRect.top - mContext.rect.top ) / height,
    ( inRect.right - mContext.rect.left ) / width,
    ( inRect.bottom - mContext.rect.top ) / height
  };
  return result;
}

class BitmapImage
GraphDisplay::BitmapData( int inWidth, int inHeight ) const
{
  int width = inWidth,
      height = inHeight,
      originalWidth = static_cast<int>( mContext.rect.right - mContext.rect.left ),
      originalHeight = static_cast<int>( mContext.rect.bottom - mContext.rect.top );
  if( width == 0 && height == 0 )
  {
    width = originalWidth;
    height = originalHeight;
  }
  BitmapImage image( width, height );
#if USE_QT
  if( mpOffscreenBmp != NULL )
  {
    BitmapImageFromQPixmap( image, *mpOffscreenBmp );
  }
  else if( mpWidget != NULL )
  {
#if _WIN32
    RECT rect = { 0, 0, originalWidth, originalHeight };
    HWND wnd = HWND( mpWidget->winId() );
    HDC dc = ::GetDC( wnd );
    BitmapImageFromHDC( image, dc, rect );
    ::ReleaseDC( wnd, dc );
#else // _WIN32
    BitmapImageFromQPixmap( image, QPixmap::grabWindow( mpWidget->winId() ) );
#endif // _WIN32
  }
#endif // USE_QT
  return image;
}

void
GraphDisplay::ClearOffscreenBuffer()
{
#if USE_QT
  delete mpOffscreenBmp;
  mpOffscreenBmp = 0;
#endif
}

#if USE_QT
WidgetBase::WidgetBase( GraphDisplay& inDisplay )
: mrGraphDisplay( inDisplay ),
  mpWidget( NULL )
{
}

WidgetBase::~WidgetBase()
{
  mrGraphDisplay.mpWidget = NULL;
}

void
WidgetBase::SetWidget( QWidget* inpWidget )
{
  mpWidget = inpWidget;
  mpWidget->setAttribute( Qt::WA_NoSystemBackground );
  mpWidget->setAutoFillBackground( false );
  mpWidget->winId();
  mpWidget->setVisible( true );
}

void
WidgetBase::OnPaintEvent( QPaintEvent* iopEvent )
{
  QRegion region = iopEvent->region().translated( mpWidget->pos() );
  mrGraphDisplay.Paint( &region );
  iopEvent->accept();
}

void
WidgetBase::OnMousePressEvent( QMouseEvent* iopEvent )
{
  if( iopEvent->button() == Qt::LeftButton )
  {
    mrGraphDisplay.Click(
      iopEvent->x() + mpWidget->pos().x(),
      iopEvent->y() + mpWidget->pos().y()
    );
    iopEvent->accept();
  }
}
#endif // USE_QT
