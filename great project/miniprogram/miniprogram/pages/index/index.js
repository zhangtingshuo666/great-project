const devicesId = "642900899" // 填写在OneNet上获得的devicesId 形式就是一串数字 例子:9939133
const api_key = "jcK5paqnhWIIrICN6duaYaINx2g=" // 填写在OneNet上的 api-key 例子: VeFI0HZ44Qn5dZO14AuLbWSlSlI=

Page({
  data:
{
 
  ceng1:'',
  ceng2:'',
  ceng3:''
},
tap1:function(){                              //页面跳转
wx.navigateTo({
  url: '../page1/page1'
})
},

tap2:function(){                             //页面跳转
  wx.navigateTo({
    url: '../page2/page2'
  })
  },

  tap3:function(){                             //页面跳转
    wx.navigateTo({
      url: '../page3/page3'
    })
    },
    
  onPullDownRefresh: function () {
    wx.showLoading({
      title: "正在获取"
    })
    this.getDatapoints().then(datapoints => {
      this.update(datapoints)
      wx.hideLoading()
    }).catch((error) => {
      wx.hideLoading()
      console.error(error)
    })
  },

 
  onLoad: function () {
    console.log(`your deviceId: ${devicesId}, apiKey: ${api_key}`)

   
   //从Onenet上获取数据 
    var that = this
    wx.request({
      url: "https://api.heclouds.com/devices/642900899/datapoints",   
      header: {
        "api-key": "jcK5paqnhWIIrICN6duaYaINx2g="                   
      },
      data: {
        limit: 1
      },
      method: "GET",
      success: function (e) {
        console.log(e.data.data)
        that.setData({
       
          ceng1:e.data.data.datastreams[0].datapoints[0].value,
          ceng2:e.data.data.datastreams[1].datapoints[0].value,
          ceng3:e.data.data.datastreams[2].datapoints[0].value,
        })
      }
    });
    wx.showLoading({
      title: '加载中'
    })

    this.getDatapoints().then((datapoints) => {
      wx.hideLoading()
    }).catch((err) => {
      wx.hideLoading()
      console.error(err)
      clearInterval(timer) 
    })
    this.getDatapoints().then((datapoints1) => {
      wx.hideLoading()
    }).catch((err) => {
      wx.hideLoading()
      console.error(err)
      clearInterval(timer) 
    })
  },

  
  getDatapoints: async function () {
    var that = this;
    return new Promise((resolve, reject) => {
      wx.request({
        url: `https://api.heclouds.com/devices/${devicesId}/datapoints?datastream_id=floor1&limit=20`,
        header: {
          'content-type': 'application/json',
          'api-key': api_key
        },
        
        
        
        success: (res) => {
          
          const status = res.statusCode
          const response = res.data
          if (status !== 200) { 
            reject(res.data)
            return ;
          }
          if (response.errno !== 0) { 
            reject(response.error)
            return ;
          }

          if (response.data.datastreams.length === 0) {
            reject("当前设备无数据, 请先运行硬件实验")
          }
           resolve({
            floor1: response.data.datastreams[0].datapoints.reverse(),
          
            
         
          })
        },
        fail: (err) => {
          reject(err)
        }
      })
    })
  }
})