{
  "الاسم": "ترويج منتج تيليجرام لشركاء AliExpress",
  "العقد": [
    {
      "حدود": {
        "قاعدة": {
          "فاصلة": [
            1
          ],
          "الساعة": 15,
          "الدقيقة": 0
        }
      },
      "id": "scheduler",
      "الاسم": "مُشغِّل بعد الظهر اليومي",
      "النوع": "n8n-nodes-base.scheduleTrigger",
      "typeVersion": 1,
      "موضع": [
        250,
        300
      ]
    },
    {
      "حدود": {
        "url": "=https://api.affiliate.aliExpress.com/query?appKey={{YOUR_APP_KEY}}&method=api.queryProducts&category=best_selling&pageSize=50",
        "خيارات": {}
      },
      "id": "fetchProducts",
      "الاسم": "جلب منتجات AliExpress",
      "النوع": "n8n-nodes-base.httpRequest",
      "typeVersion": 1,
      "موضع": [
        450,
        300
      ]
    },
    {
      "حدود": {
        "jsCode": "// تصفية وتحديد أفضل 30 منتجًا\nconst products = $input.first().json.data.products;\nconst filteredProducts = products\n .filter(product => product.shippingType === 'DDP') // تصفية منتجات DDP\n .slice(0, 30); // تحديد أفضل 30\n\nreturn filteredProducts.map(product => ({\n json: product\n}));"
      },
      "id": "processProducts",
      "الاسم": "معالجة وتصفية المنتجات",
      "النوع": "n8n-nodes-base.code",
      "typeVersion": 1,
      "موضع": [
        650,
        300
      ]
    },
    {
      "حدود": {
        "العملية": "الرسالة",
        "النص": "={{ $json.title }}\\n\\nالسعر: ${{ $json.price }}\\n\\n{{ $json.productUrl }}",
        "الحقول الإضافية": {}
      },
      "id": "telegramNode",
      "الاسم": "نشر على تيليجرام",
      "النوع": "n8n-nodes-base.telegram",
      "typeVersion": 1,
      "موضع": [
        1050,
        300
      ],
      "أوراق اعتماد": {
        "telegramApi": {
          "id": "معرف بيانات اعتمادك على الهاتف",
          "الاسم": "واجهة برمجة تطبيقات تيليجرام"
        }
      }
    },
    {
      "حدود": {
        "القيمة": 2,
        "الوحدة": "الدقائق"
      },
      "id": "delayNode",
      "الاسم": "التأخير بين المنشورات",
      "النوع": "n8n-nodes-base.wait",
      "typeVersion": 1,
      "موضع": [
        850,
        300
      ]
    }
  ],
  "الاتصالات": {
    "مُشغِّل بعد الظهر اليومي": {
      "رئيسي": [
        [
          {
            "node": "جلب منتجات AliExpress",
            "النوع": "الرئيسي",
            "الفهرس": 0
          }
        ]
      ]
    },
    "جلب منتجات AliExpress": {
      "رئيسي": [
        [
          {
            "node": "معالجة وتصفية المنتجات",
            "النوع": "الرئيسي",
            "الفهرس": 0
          }
        ]
      ]
    },
    "معالجة وتصفية المنتجات": {
      "رئيسي": [
        [
          {
            "node": "التأخير بين المنشورات",
            "النوع": "الرئيسي",
            "الفهرس": 0
          }
        ]
      ]
    },
    "التأخير بين المنشورات": {
      "رئيسي": [
        [
          {
            "node": "نشر على تيليجرام",
            "النوع": "الرئيسي",
            "الفهرس": 0
          }
        ]
      ]
    }
  },
  "pinData": {},
  "معرف الإصدار": "1",
  "تم الإنشاء في": 1693065600000,
  "تم التحديث في": 1693065600000,
  "إعدادات": {
    "أمر التنفيذ": "v1"
  },
  "staticData": null,
  "العلامات": []
}
