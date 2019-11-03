library(shiny)
library(miniUI)

upload_data <- function() {
  server <- shinyServer(function(input, output) {
    options(shiny.maxRequestSize = 300 * 1024^2)
    
    out <- NULL
    observeEvent(input$file1$datapath, {
      withCallingHandlers({
        shinyjs::html("text", "")

        message("Parsing Tweets...")
        out <<- tweetio::read_tweets(input$file1$datapath, type = "nested_doc")

        message("Done!")
      },
      message = function(m) shinyjs::html(id = "text", html = m$message, add = TRUE)
      )})
    
    
    observeEvent(input$done, {
      req(out)
      stopApp(returnValue = out)
    })
    
  })
  
  
  ui <- miniPage(
    gadgetTitleBar("{tweetio}")
    ,
    sidebarLayout(
      sidebarPanel(
        fileInput(inputId = "file1", label = "Upload File",
                  multiple = FALSE,
                  accept = c(".json", ".jsonl", ".gz", ".zip"))
      )
      ,
      miniContentPanel(
        shinyjs::useShinyjs(),
        verbatimTextOutput("text")
      )
    )
  )
  
  runGadget(ui, server)
}

test <- upload_data()

